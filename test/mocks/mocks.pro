TEMPLATE = lib

include(../../test.pri)

CONFIG += staticlib

check.depends += all
QMAKE_EXTRA_TARGETS += check

include(../../report.pri)

# maemo related emulation
#HEADERS += \

#SOURCES += \

TARGET = mock

