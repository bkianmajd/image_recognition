!contains(included_modules, $$PWD ) {
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/poker_landmark_generator/poker_landmark_generator.h
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/poker_landmark_generator/indicator_finder.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/poker_landmark_generator/poker_landmark_generator.cpp
SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/poker_landmark_generator/indicator_finder.cpp

include($${WORKSPACE}/components/image_recognition/image_recognition.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/libraries/screenshot_creator/screenshot_creator.pri)
include($${WORKSPACE}/components/poker/poker_game_controller/definitions/definitions.pri)
}
