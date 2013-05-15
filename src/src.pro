TEMPLATE      = lib

include(../product.pri)

DEFINES += APP_NAME=\\\"\"regionformat\"\\\"

CONFIG += plugin
#CONFIG += cellular-qt

target.path += $$DCP_APPLET_DIR


include(../report.pri)


HEADERS += \
	debug.h \
	drilldownitem.h \
	viewid.h \
	titlewidget.h \
        regionconf.h \
	regionmodel.h \
	regioncell.h \
	businesslogic.h \
	translation.h \
	infoitem.h \
	widgetlist.h \
	regionview.h \
	mainview.h \
	brief.h \
	applet.h

SOURCES += \
	debug.cpp \
	drilldownitem.cpp \
        regionconf.cpp \
	regionmodel.cpp \
	businesslogic.cpp \
	translation.cpp \
	infoitem.cpp \
	widgetlist.cpp \
	regionview.cpp \
	mainview.cpp \
	brief.cpp \
	applet.cpp


TARGET        = $$qtLibraryTarget(regionformat)
INSTALLS += target

