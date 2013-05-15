include(../head.pri)

TESTNAME = ut_regionconf

SOURCES += $$SRCDIR/regionconf.cpp \
        $$SRCDIR/debug.cpp \
        $$TOOLSDIR/stubbase.cpp

HEADERS += $$SRCDIR/regionconf.h \
        $$SRCDIR/debug.h \
        $$TOOLSDIR/stubbase.h

include(../tail.pri)

