include(../head.pri)

TESTNAME = ut_infoitem

SOURCES += $$SRCDIR/infoitem.cpp \
        $$SRCDIR/debug.cpp \
        $$TOOLSDIR/stubbase.cpp

HEADERS += $$SRCDIR/infoitem.h \
        $$SRCDIR/debug.h \
        $$MOCKSDIR/mabstractlayoutpolicy-fake.h \
        $$MOCKSDIR/mlayout-fake.h \
        $$MOCKSDIR/mlinearlayoutpolicy-fake.h \
        $$MOCKSDIR/mcontainer-fake.h \
        $$MOCKSDIR/mwidgetcontroller-fake.h \
        $$TOOLSDIR/stubbase.h

include(../tail.pri)

