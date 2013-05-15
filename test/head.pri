TEMPLATE = app

DEFINES += \
        UNIT_TEST

PKGROOT="../.."
include($$PKGROOT/test.pri)

SRCDIR="../../src/"

DOUBLESDIR="../doubles/"

MOCKSDIR="../mocks/"

TOOLSDIR="../tools/"

CONFIG += qtestlib
QT += testlib

DEFINES += APP_NAME=\\\"\"regionformat-test\"\\\"

INCLUDEPATH += $$SRCDIR
INCLUDEPATH += $$TOOLSDIR
INCLUDEPATH += $$DOUBLESDIR
INCLUDEPATH += $$MOCKSDIR

QMAKE_LIBDIR += $$TOOLSDIR
LIBS += -ltools

target.path += $${PREFIX}/lib/duicontrolpanel-regionformatapplet-tests

include($$PKGROOT/report.pri)

