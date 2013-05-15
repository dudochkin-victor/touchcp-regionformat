TEMPLATE = lib

include(../../test.pri)

CONFIG += staticlib

check.depends += all
QMAKE_EXTRA_TARGETS += check

include(../../report.pri)

HEADERS += testtools.h \
	signalchecker.h

SOURCES += testtools.cpp \
	signalchecker.cpp

TARGET = tools

