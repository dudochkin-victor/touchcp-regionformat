TEMPLATE = subdirs

CONFIG = conf

include(product.pri)
include(data/data.pri)

SUBDIRS += src translations test


check.commands = cd test ; qmake ; make check ; cd ..
QMAKE_EXTRA_TARGETS += check


