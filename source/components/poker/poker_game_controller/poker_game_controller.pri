!contains(included_modules, $$PWD ) {
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/poker_game_controller.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/poker_game_controller.cpp


include($${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/landmark_finder.pri)
}
