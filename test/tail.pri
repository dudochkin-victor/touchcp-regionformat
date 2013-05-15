
SOURCES += $${TESTNAME}.cpp

TARGET = $${TESTNAME} # integration test
TARGET.depends += $${TESTNAME}.moc # hack to force .moc generation

INSTALLS += target

check.depends = $$TARGET                                                                                                                                                                                   
check.commands = rm .bcovdump ; echo `bcov ./$$TARGET | tail -n 2 | head -n 1` test: $$TARGET >> ../result.txt ; cat .bcovdump >> ../.bcovdump ; mkdir bcov ; bcov-report .bcovdump bcov/                  
QMAKE_EXTRA_TARGETS += check                                                                                                                                                                               
																									   QMAKE_CLEAN += .bcovdump bcov/** 
