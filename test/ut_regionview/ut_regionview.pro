include(../head.pri)

TESTNAME = ut_regionview

SOURCES += $$SRCDIR/regionview.cpp \
        $$SRCDIR/debug.cpp \
        $$TOOLSDIR/stubbase.cpp

HEADERS += $$SRCDIR/regionview.h \
        $$SRCDIR/debug.h \
        $$SRCDIR/businesslogic.h \ 
        $$SRCDIR/regionmodel.h \ 
        $$SRCDIR/regioncell.h \ 
        $$SRCDIR/regionheadercell.h \ 
        $$MOCKSDIR/mgconfitem-fake.h \
        $$MOCKSDIR/gconfitemprivate-fake.h \
        $$MOCKSDIR/mabstractlayoutpolicy-fake.h \
        $$MOCKSDIR/mcontentitem-fake.h \
        $$MOCKSDIR/mlayout-fake.h \
        $$MOCKSDIR/mlinearlayoutpolicy-fake.h \
        $$MOCKSDIR/mwidgetcontroller-fake.h \
        $$MOCKSDIR/mlist-fake.h \
        $$DOUBLESDIR/regionmodel-stub.h \
        $$DOUBLESDIR/businesslogic-stub.h \
        $$TOOLSDIR/stubbase.h 

include(../tail.pri)

