TEMPLATE = aux

UNIT_TEST_BINARIES = \
    $$PWD/build/fbrecurring \
    $$PWD/build/loadcalendar \
    $$PWD/build/readandwrite \
    $$PWD/build/testalarm \
    $$PWD/build/testattachment \
    $$PWD/build/testattendee \
    $$PWD/build/testcalfilter \
    $$PWD/build/testcreateddatecompat \
    $$PWD/build/testcustomproperties \
    $$PWD/build/testduration \
    $$PWD/build/testevent \
    $$PWD/build/testexception \
    $$PWD/build/testfb \
    $$PWD/build/testfilestorage \
    $$PWD/build/testfreebusy \
    $$PWD/build/testicalformat \
    $$PWD/build/testicaltimezones \
    $$PWD/build/testincidencerelation \
    $$PWD/build/testjournal \
    $$PWD/build/testmemorycalendar \
    $$PWD/build/testperiod \
    $$PWD/build/testperson \
    $$PWD/build/testrecurprevious \
    $$PWD/build/testrecurrence \
    $$PWD/build/testrecurrencetype \
    $$PWD/build/testrecurson \
    $$PWD/build/testrecurtodo \
    $$PWD/build/testsortablelist \
    $$PWD/build/testtimesininterval \
    $$PWD/build/testtodo \
    $$PWD/build/testtostring \
    $$PWD/build/testvcalexport

buildtests.commands += mkdir -p $$PWD/build && cd $$PWD/build && cmake .. && make
buildtests.CONFIG += no_check_exist
buildtests.output = $$UNIT_TEST_BINARIES
buildtests.input = tests

buildtests_install.files = $$UNIT_TEST_BINARIES
buildtests_install.path = $$INSTALL_ROOT/opt/tests/kcalcoren-qt5/
buildtests_install.CONFIG += no_check_exist

QMAKE_EXTRA_TARGETS += buildtests
PRE_TARGETDEPS += buildtests
INSTALLS += buildtests_install
