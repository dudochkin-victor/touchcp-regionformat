#
#       remove everything we want to set by ourselves
#
CONFIG -= lex yacc uic resources incremental link_prl nostrip exceptions no_mocdepend stl qt_no_framework qt warn_on release debug build_all silent thread

#
#       Start to configure
#

QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS += -g

CONFIG += qt no_mocdepend
CONFIG += gui meegotouch duicontrolpanel
CONFIG += build_all warn_on
CONFIG += nostrip
CONFIG += stl
CONFIG += ordered
#CONFIG += silent

#FIXME get prefix from environment or debian rules file
PREFIX = /usr


#
#       Dependency on DCP
#

include ($$[QT_INSTALL_DATA]/mkspecs/dcpconfig.pri)
PREFIX = $$DCP_PREFIX
CONFIG += meegotouchcontrolpanel

#
# Path of region config
#
REGION_CONF_FILENAME = meego-supported-regions.conf
REGION_CONF_DIR = /etc
REGION_CONF_PATH = $$REGION_CONF_DIR/$$REGION_CONF_FILENAME
DEFINES += REGION_CONF_PATH=\\\"$${REGION_CONF_PATH}\\\"

#
# try to detect maemo environment
#

MAEMOTARGET = $$system(cpp -dM /dev/null | grep ARM)
!isEmpty(MAEMOTARGET){
	CONFIG += maemo
}
maemo{
	DEFINES += MAEMO
}

OBJECTS_DIR = .obj
MOC_DIR = .moc

QMAKE_CLEAN += .obj/* .moc/*

#
# some debugging related config both for tests and product
#
QMAKE_CXXFLAGS += -finstrument-functions-exclude-file-list=/bits/stl,include/sys,debug,qt,meego,qmsystem,string,unistd,include/unicode
QMAKE_CXXFLAGS += -finstrument-functions-exclude-function-list=new,metaObject,qt_metacall

