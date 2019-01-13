!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/map_images/value_comparer.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/map_images/value_comparer.cpp

}
