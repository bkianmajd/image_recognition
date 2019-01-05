!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/card_reader/card_reader.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/card_reader/card_reader.cpp

include($${WORKSPACE}/libraries/screenshot_creator/screenshot_creator.pri)
include($${WORKSPACE}/libraries/image_recognition/image_recognition.pri)
include($${WORKSPACE}/components/poker/entities/entities.pri)
}
