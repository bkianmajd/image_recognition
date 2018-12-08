QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}components/poker/poker_game_controller/landmark_finder/area_finder/area_finder_test.cpp

include($${WORKSPACE}components/poker/poker_game_controller/landmark_finder/area_finder/area_finder.pri)
