include(../head.pri)

TESTNAME = ut_applet

SOURCES += $$SRCDIR/applet.cpp \
        $$SRCDIR/debug.cpp \
        $$TOOLSDIR/stubbase.cpp

HEADERS += $$SRCDIR/applet.h \
        $$SRCDIR/brief.h \
        $$SRCDIR/debug.h \
        $$SRCDIR/regionview.h \ 
        $$SRCDIR/mainview.h \ 
        $$SRCDIR/viewid.h \ 
        $$SRCDIR/translation.h \ 
        $$DOUBLESDIR/brief-stub.h \
        $$DOUBLESDIR/regionview-stub.h \ 
        $$DOUBLESDIR/mainview-stub.h \
        $$TOOLSDIR/stubbase.h 


include(../tail.pri)

