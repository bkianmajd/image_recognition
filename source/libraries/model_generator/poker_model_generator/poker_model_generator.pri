!contains(included_modules, $$PWD ) {

HEADERS += $${WORKSPACE}/libraries/model_generator/poker_model_generator/poker_model_generator.h
HEADERS += $${WORKSPACE}/libraries/model_generator/poker_model_generator/poker_model_generator_mock.hpp
HEADERS += $${WORKSPACE}/libraries/model_generator/poker_model_generator/poker_model_def.h
HEADERS += $${WORKSPACE}/libraries/model_generator/poker_model_generator/card_def.h

SOURCES += $${WORKSPACE}/libraries/model_generator/poker_model_generator/poker_model_generator.cpp

include($${WORKSPACE}/libraries/model_generator/model_generator.pri)
}
