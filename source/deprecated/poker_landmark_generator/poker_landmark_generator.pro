QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../source/
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/google_test/widget_main.cpp
SOURCES += $${WORKSPACE}components/poker/poker_game_controller/poker_landmark_generator/poker_landmark_generator_test.cpp
SOURCES += $${WORKSPACE}components/poker/poker_game_controller/poker_landmark_generator/indicator_finder_test.cpp

include(poker_landmark_generator.pri)
