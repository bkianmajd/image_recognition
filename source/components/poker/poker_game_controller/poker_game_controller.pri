!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/poker_game_controller_interface.h
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/poker_game_controller.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/poker_game_controller.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
include($${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/landmark_finder.pri)
include($${WORKSPACE}/external_libraries/libchrome_output/libchrome_output.pri)
}
