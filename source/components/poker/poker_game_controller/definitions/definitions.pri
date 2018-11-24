!contains(included_modules, $$PWD ) {
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/definitions/landmark_config_def.h
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/definitions/six_player_config.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/definitions/six_player_config.cpp
}
