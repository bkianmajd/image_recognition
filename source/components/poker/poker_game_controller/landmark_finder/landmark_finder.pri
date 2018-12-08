!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/landmark_finder.h
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/map_to_card_converter.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/landmark_finder.cpp
SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/map_to_card_converter.cpp


include($${WORKSPACE}/libraries/screenshot_creator/screenshot_creator.pri)
include($${WORKSPACE}/components/image_recognition/image_recognition.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/area_finder/area_finder.pri)

}
