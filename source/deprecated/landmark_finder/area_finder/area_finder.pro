QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../../source/
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/google_test/widget_main.cpp
SOURCES += $${WORKSPACE}components/poker/poker_game_controller/landmark_finder/area_finder/area_finder_test.cpp

include($${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/area_finder/area_finder.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
