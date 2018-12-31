QT += core
QT -= gui

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/widget_main.cpp
SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/table_locator/table_locator_test.cpp

include($${WORKSPACE}/components/poker/poker_game_controller/landmark_finder/table_locator/table_locator.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
