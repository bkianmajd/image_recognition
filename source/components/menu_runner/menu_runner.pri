!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/menu_runner/menu_runner.h

SOURCES += $${WORKSPACE}/components/menu_runner/menu_runner.cpp

include($${WORKSPACE}/components/poker/poker_workflow.pri)
}
