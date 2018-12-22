!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/poker_workflow.h

SOURCES += $${WORKSPACE}/components/poker/poker_workflow.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
include($${WORKSPACE}/components/poker/poker_game_controller/poker_game_controller.pri)
include($${WORKSPACE}/components/poker/poker_game_controller/training/training.pri)
}
