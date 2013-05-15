include(../head.pri)

TESTNAME = ut_widgetlist

SOURCES += $$SRCDIR/widgetlist.cpp \
        $$SRCDIR/debug.cpp \
        $$TOOLSDIR/stubbase.cpp

HEADERS += $$SRCDIR/widgetlist.h \
        $$SRCDIR/debug.h \
        $$MOCKSDIR/mabstractlayoutpolicy-fake.h \
        $$MOCKSDIR/mlayout-fake.h \
        $$MOCKSDIR/mgridlayoutpolicy-fake.h \
        $$MOCKSDIR/mlinearlayoutpolicy-fake.h \
        $$TOOLSDIR/stubbase.h

include(../tail.pri)

