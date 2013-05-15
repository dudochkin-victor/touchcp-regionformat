include(../head.pri)

TESTNAME = ut_regionmodel

SOURCES += $$SRCDIR/regionmodel.cpp \
        $$SRCDIR/debug.cpp \
        $$TOOLSDIR/stubbase.cpp

HEADERS += $$SRCDIR/regionmodel.h \
        $$SRCDIR/regionconf.h \
        $$SRCDIR/debug.h \
        $$MOCKSDIR/mlocale-fake.h \
        $$DOUBLESDIR/regionconf-stub.h \
        $$TOOLSDIR/stubbase.h 

include(../tail.pri)

