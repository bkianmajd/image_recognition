!contains(included_modules, $$PWD ) {

HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/poker_model_generator/poker_model_generator.h
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/poker_model_generator/poker_model_generator_mock.hpp
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/poker_model_generator/poker_model_def.h
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/poker_model_generator/card_def.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/poker_model_generator/poker_model_generator.cpp

include($${WORKSPACE}/libraries/model_generator/model_generator.pri)
}
