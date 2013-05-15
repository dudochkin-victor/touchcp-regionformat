include(../head.pri)

TESTNAME = ut_businesslogic

SOURCES += $$SRCDIR/businesslogic.cpp \
        $$SRCDIR/debug.cpp \
        $$TOOLSDIR/stubbase.cpp

HEADERS += $$SRCDIR/businesslogic.h \
        $$SRCDIR/debug.h \
        $$SRCDIR/regionmodel.h \
        $$MOCKSDIR/qdatetime-fake.h \
        $$MOCKSDIR/mlocale-fake.h \
        $$DOUBLESDIR/regionmodel-stub.h \
        $$MOCKSDIR/gconfitemprivate-fake.h \
        $$MOCKSDIR/mgconfitem-fake.h \
        $$TOOLSDIR/stubbase.h

include(../tail.pri)

