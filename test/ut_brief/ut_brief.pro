include(../head.pri)

TESTNAME = ut_brief

SOURCES += $$SRCDIR/brief.cpp \
        $$SRCDIR/debug.cpp \
        $$TOOLSDIR/stubbase.cpp

HEADERS += $$SRCDIR/brief.h \
        $$SRCDIR/debug.h \
        $$MOCKSDIR/mgconfitem-fake.h \
        $$MOCKSDIR/gconfitemprivate-fake.h \
        $$SRCDIR/businesslogic.h \ 
        $$DOUBLESDIR/businesslogic-stub.h \ 
        $$TOOLSDIR/stubbase.h 

include(../tail.pri)

