TEMPLATE = lib
equals(QT_MAJOR_VERSION, 4): TARGET = kcalcoren
equals(QT_MAJOR_VERSION, 5): TARGET = kcalcoren-qt5
DEPENDPATH += . tests versit klibport kdedate
INCLUDEPATH += . versit klibport kdedate tests /usr/include/libical

VERSION += 4.10.2

CONFIG += link_pkgconfig
PKGCONFIG += libical
equals(QT_MAJOR_VERSION, 4): PKGCONFIG += timed
equals(QT_MAJOR_VERSION, 5): PKGCONFIG += timed-qt5

DEFINES += MEEGO \
    UUID \
    KCALCORE_FOR_MEEGO \
    TIMED_SUPPORT

QT += dbus

target.path = $$INSTALL_ROOT/usr/lib
equals(QT_MAJOR_VERSION, 4): headers.path += $$INSTALL_ROOT/usr/include/kcalcoren
equals(QT_MAJOR_VERSION, 5): headers.path += $$INSTALL_ROOT/usr/include/kcalcoren-qt5
headers.files += *.h \
    kdedate/*.h \
    kdedate/KDateTime \
    kdedate/KSystemTimeZone \
    kdedate/KSystemTimeZones \
    klibport/KCodecs \
    klibport/KConfig \
    klibport/KCondigGroup \
    klibport/KDebug \
    klibport/KRandom \
    klibport/KSaveFile \
    klibport/KStandardDirs \
    klibport/KUrl \
    klibport/*.h

pkgconfig.path = $$INSTALL_ROOT/usr/lib/pkgconfig
equals(QT_MAJOR_VERSION, 4): pkgconfig.files = ../libkcalcoren.pc
equals(QT_MAJOR_VERSION, 5): pkgconfig.files = ../libkcalcoren-qt5.pc

INSTALLS += target \
    headers \
    pkgconfig

# Input
HEADERS += alarm.h \
           attachment.h \
           attendee.h \
           calendar.h \
           calfilter.h \
           calformat.h \
           calstorage.h \
           compat.h \
           customproperties.h \
           duration.h \
           event.h \
           exceptions.h \
           filestorage.h \
           freebusy.h \
           freebusycache.h \
           freebusyperiod.h \
#           freebusyurlstore.h \
           icalformat.h \
           icalformat_p.h \
           icaltimezones.h \
           incidence.h \
           incidencebase.h \
           invitationhandlerif.h \
           journal.h \
           kcalcore_export.h \
           memorycalendar.h \
           period.h \
           person.h \
           recurrence.h \
           recurrencerule.h \
           schedulemessage.h \
           sortablelist.h \
           sorting.h \
           supertrait.h \
           todo.h \
           vcalformat.h \
           visitor.h \
    kdedate/kcalendarsystem.h \
    kdedate/KSystemTimeZone \
    kdedate/kcalendarsystemgregorian.h \
    kdedate/kcalendarsystemhebrew.h \
    kdedate/kcalendarsystemhijri.h \
    kdedate/kcalendarsystemjalali.h \
    klibport/kcodecs.h \
    kdedate/kdatetime.h \
    klibport/meego_port.h \
    kdedate/ksystemtimezone.h \
    kdedate/ktimezone.h \
    kdedate/ktzfiletimezone.h \
    klibport/kapplication.h \
    klibport/kcmdlineargs.h \
    klibport/kcomponentdata.h \
    klibport/KConfig \
    klibport/kde_static.h \
    klibport/KDebug \
    klibport/kdebug.h \
    klibport/klocale.h \
    klibport/KRandom \
    klibport/global.h \
    klibport/kglobal.h \
    klibport/KSaveFile \
    klibport/KCodecs  \
    klibport/KUrl \
    klibport/config.h \
    klibport/kstringhandler.h \
    klibport/ktemporaryfile.h \
    klibport/KConfigGroup \
    klibport/kconfiggroup.h \
    klibport/kpimutils/email.h \
    klibport/KStandardDirs \
    klibport/kaboutdata.h \
    klibport/qtest_kde.h \
    klibport/incidenceformatter.h \
    klibport/kdemacros.h \
    klibport/qtest_kde.h \
    klibport/meego_port.h \
    klibport/ktemporaryfile.h \
    klibport/kstringhandler.h \
    klibport/klocale.h \
    klibport/kde_static.h \
    klibport/kdemacros.h \
    klibport/kdecore_export.h \
    klibport/kcomponentdata.h \
    klibport/KCodecs \
    klibport/kcmdlineargs.h \
    klibport/kapplication.h \
    klibport/kaboutdata.h \
    klibport/incidenceformatter.h \
    klibport/config.h

#YACCSOURCES += versit/vcc.y

SOURCES += alarm.cpp \
           attachment.cpp \
           attendee.cpp \
           calendar.cpp \
           calfilter.cpp \
           calformat.cpp \
           calstorage.cpp \
           compat.cpp \
           customproperties.cpp \
           duration.cpp \
           event.cpp \
           exceptions.cpp \
           filestorage.cpp \
           freebusy.cpp \
           freebusycache.cpp \
           freebusyperiod.cpp \
#           freebusyurlstore.cpp \
           icalformat.cpp \
           icalformat_p.cpp \
           icaltimezones.cpp \
           incidence.cpp \
           incidencebase.cpp \
           journal.cpp \
           memorycalendar.cpp \
           period.cpp \
           person.cpp \
           recurrence.cpp \
           recurrencerule.cpp \
           schedulemessage.cpp \
           sorting.cpp \
           todo.cpp \
           vcalformat.cpp \
           visitor.cpp \
           versit/vcc.c \
           versit/vobject.c\
#           kdatetimeoperators.cpp \
    klibport/meego_port.cpp \
    kdedate/kcalendarsystem.cpp \
    kdedate/kcalendarsystemgregorian.cpp \
    kdedate/kcalendarsystemhebrew.cpp \
    kdedate/kcalendarsystemhijri.cpp \
    kdedate/kcalendarsystemjalali.cpp \
    kdedate/kdatetime.cpp \
    kdedate/ksystemtimezone.cpp \
    kdedate/ktimezone.cpp \
    kdedate/ktzfiletimezone.cpp \
    klibport/kcodecs.cpp \
    klibport/global.cpp
