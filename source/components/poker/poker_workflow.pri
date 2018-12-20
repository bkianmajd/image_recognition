!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/poker_workflow.h

SOURCES += $${WORKSPACE}/components/poker/poker_workflow.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
}
