include(../head.pri)

TESTNAME = ut_mainview

SOURCES += $$SRCDIR/mainview.cpp \
        $$SRCDIR/debug.cpp \
        $$TOOLSDIR/stubbase.cpp

HEADERS += $$SRCDIR/mainview.h \
        $$SRCDIR/debug.h \
        $$MOCKSDIR/mgconfitem-fake.h \
        $$MOCKSDIR/gconfitemprivate-fake.h \
        $$SRCDIR/translation.h \ 
        $$SRCDIR/widgetlist.h \ 
        $$SRCDIR/infoitem.h \ 
        $$SRCDIR/businesslogic.h \ 
        $$SRCDIR/translation.h \ 
        $$SRCDIR/drilldownitem.h \ 
        $$DOUBLESDIR/businesslogic-stub.h \
        $$DOUBLESDIR/brief-stub.h \
        $$DOUBLESDIR/infoitem-stub.h \
        $$DOUBLESDIR/widgetlist-stub.h \
        $$DOUBLESDIR/drilldownitem-stub.h \
        $$MOCKSDIR/mabstractlayoutpolicy-fake.h \
        $$MOCKSDIR/mlayout-fake.h \
        $$MOCKSDIR/mlinearlayoutpolicy-fake.h \
        $$MOCKSDIR/mcontentitem-fake.h \
        $$MOCKSDIR/mcontainer-fake.h \
        $$MOCKSDIR/mcombobox-fake.h \
        $$TOOLSDIR/stubbase.h 

include(../tail.pri)

