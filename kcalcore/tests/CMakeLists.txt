cmake_minimum_required(VERSION 2.8.11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5Test)

include_directories(${LIBICAL_INCLUDE_DIRS} ${QT_INCLUDE_DIRS} ../ ../versit ../klibport ../kdedate)

macro (KCALCORE_ADD_UNIT_TEST _test_NAME)
    kcalcore_add_executable(${_test_NAME} ${ARGN})
    set(_executable ${EXECUTABLE_OUTPUT_PATH}/${_test_NAME})
endmacro (KCALCORE_ADD_UNIT_TEST)

macro (KCALCORE_ADD_EXECUTABLE _target_NAME)
    set(_type "NOGUI")
    set(_add_executable_param)
    set(_type "RUN_UNINSTALLED ${_type}")
    add_executable(${_target_NAME} ${_add_executable_param} ${ARGN})
    set_target_properties(${_target_NAME} PROPERTIES COMPILE_FLAGS -DKDESRCDIR="\\"${CMAKE_CURRENT_SOURCE_DIR}\\"")
endmacro (KCALCORE_ADD_EXECUTABLE)

macro(macro_unit_tests)
  foreach(_testname ${ARGN})
    kcalcore_add_unit_test(${_testname} ${_testname}.cpp)
    target_link_libraries(${_testname}
      ${LIBICAL_LIBRARIES}
      ical
      Qt5::Core
      Qt5::Test
      kcalcoren-qt5
    )
  endforeach()
endmacro()

macro(macro_exec_tests)
  foreach(_testname ${ARGN})
    kcalcore_add_executable(${_testname} ${_testname}.cpp)
    target_link_libraries(${_testname}
      ical
      Qt5::Core
      Qt5::Test
      kcalcoren-qt5
    )
  endforeach()
endmacro()

macro_unit_tests(
  testalarm
  testattachment
  testattendee
  testcalfilter
  testcustomproperties
  testduration
  testevent
  testexception
  testfilestorage
  testfreebusy
  testincidencerelation
  testicalformat
  testjournal
  testmemorycalendar
  testperiod
  testperson
  testrecurtodo
  testsortablelist
  testtodo
  testtimesininterval
  testcreateddatecompat
)

set_target_properties(testmemorycalendar PROPERTIES COMPILE_FLAGS -DICALTESTDATADIR="\\"${CMAKE_SOURCE_DIR}/kcalcore/tests/data/\\"" )

# this test cannot work with msvc because libical should not be altered
# and therefore we can't add KCALCORE_EXPORT there
# it should work fine with mingw because of the auto-import feature
# KDAB_TODO: check if this can build with msvc now (and if it works on Windows)
if(NOT MSVC)
  macro_unit_tests(testicaltimezones)
endif()

macro_exec_tests(
  incidencestest
  loadcalendar
  fbrecurring
  readandwrite
  testfb
  testrecurprevious
  testrecurrence
  testrecurrencetype
  testrecurson
  testtostring
  testvcalexport
)

########### Tests #######################

file(GLOB_RECURSE testFiles data/RecurrenceRule/*.ics)
file(GLOB_RECURSE compatFiles data/Compat/*.ics)
file(GLOB_RECURSE vCalFilesAsIcal data/vCalendar/*.ics)
file(GLOB_RECURSE vCalFiles data/vCalendar/*.vcs)

if(WIN32)
  find_program(PERL_EXECUTABLE perl)
endif()

macro(kcalcore_run_single_test _prefix _f _test _testarg)
  get_filename_component(_fn ${_f} NAME)

  # Write the output file in the build directory.
  string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" _outFile ${_f})
  get_filename_component(_outputPath ${_outFile} PATH)
  file(MAKE_DIRECTORY ${_outputPath})

  set(_runner ${CMAKE_CURRENT_SOURCE_DIR}/runsingletestcase.pl)
  if(UNIX)
    set(_test_path ${EXECUTABLE_OUTPUT_PATH}/${_test}.shell)
  endif()
  if(WIN32)
    set(_test_path ${EXECUTABLE_OUTPUT_PATH}/${_test}.exe.bat)
    set(_runner ${PERL_EXECUTABLE} ${_runner})
  endif()

  add_test(${_prefix}-${_fn} ${_runner} ${_test_path} ${_testarg} ${_f} ${_outFile})
endmacro()

file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/FAILED.log)

foreach(file ${testFiles})
  kcalcore_run_single_test(RecurNext ${file} testrecurrence "next")
endforeach()

foreach(file ${testFiles})
  kcalcore_run_single_test(RecurPrev ${file} testrecurprevious "prev")
endforeach()

foreach(file ${testFiles})
  kcalcore_run_single_test(RecursOn ${file} testrecurson "recurson")
endforeach()

foreach(file ${compatFiles})
  kcalcore_run_single_test(Compat ${file} readandwrite "ical")
endforeach()

foreach(file ${vCalFilesAsIcal})
  kcalcore_run_single_test(VCalOut ${file} testvcalexport "vcal")
endforeach()

foreach(file ${vCalFiles})
  kcalcore_run_single_test(VCalIn ${file} readandwrite "ical")
endforeach()
