QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/widget_main.cpp
SOURCES += $${WORKSPACE}components/poker/poker_game_controller/poker_landmark_generator/poker_landmark_generator_test.cpp
SOURCES += $${WORKSPACE}components/poker/poker_game_controller/poker_landmark_generator/indicator_finder_test.cpp

include(poker_landmark_generator.pri)
