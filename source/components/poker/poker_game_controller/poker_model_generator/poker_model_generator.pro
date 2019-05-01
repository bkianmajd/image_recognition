QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../source/
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/poker_model_generator/poker_model_generator_test.cpp

include($${WORKSPACE}/components/poker/poker_game_controller/poker_model_generator/poker_model_generator.pri)
