TEMPLATE    = subdirs

include(shell.pri)

include(../test.pri)

SUBDIRS =	tools

check.commands = "true "

UNIT_TESTING=$$(UNIT_TESTING)
!contains(UNIT_TESTING, no){
	SUBDIRS += ut_applet \
			ut_drilldownitem \
			ut_brief \
			ut_businesslogic \
			ut_infoitem \
			ut_mainview \
			ut_regionmodel \
			ut_regionview \
                        ut_regionconf \
			ut_widgetlist
        check.commands += rm report.txt ; ./report-summarize.awk < result.txt >> report.txt; ./coverage.perl ; mkdir bcov ; bcov-report .bcovdump.res bcov/ ; rm result.txt
	check.commands += ; cat ./report.txt
        check.depends += all
} else {
	dummy_file.commands += touch $$OUT_PWD/keep_this_dir
	dummy_file.target = dummy_file
	dummy_file.files += $$OUT_PWD/keep_this_dir
	dummy_file.path = $$PREFIX/share/duicontrolpanel-regionformatapplet-tests
	INSTALLS += dummy_file
	dummy_libfile.commands += touch $$OUT_PWD/keep_this_dir
	dummy_libfile.target = dummy_file
	dummy_libfile.files += $$OUT_PWD/keep_this_dir
	dummy_libfile.path = $$PREFIX/lib/duicontrolpanel-regionformatapplet-tests
	INSTALLS += dummy_file dummy_libfile

}


check.CONFIG += recursive
QMAKE_EXTRA_TARGETS += check

testsxml.files += runtests.sh tests.xml
testsxml.path += $$PREFIX/share/duicontrolpanel-regionformatapplet-tests
INSTALLS += testsxml


QMAKE_CLEAN += coverage.txt result.txt report.txt .bcovdump .bcovdump.res bcov/**
