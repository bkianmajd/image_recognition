!contains(included_modules, $$PWD ) {
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/area_finder/area_finder.h
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/area_finder/six_player_area_finder.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/area_finder/six_player_area_finder.cpp

include($${WORKSPACE}/libraries/screenshot_creator/screenshot_creator.pri)
}
