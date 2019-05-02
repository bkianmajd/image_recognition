!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/landmark_finder.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/landmark_finder.cpp


include($${WORKSPACE}/libraries/screenshot_creator/screenshot_creator.pri)
include($${WORKSPACE}/libraries/image_recognition/image_recognition.pri)
include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/card_reader/card_reader.pri)
include($${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/player_locator/player_locator.pri)
include($${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/table_locator/table_locator.pri)
}
