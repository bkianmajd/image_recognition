!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/table_locator/table_locator.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/table_locator/table_locator.cpp

include($${WORKSPACE}/libraries/screenshot_creator/screenshot_creator.pri)
}
