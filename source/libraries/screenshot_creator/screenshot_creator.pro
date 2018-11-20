QT += core
QT += widgets
QT += gui


CONFIG += c++11

WORKSPACE = ../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/widget_main.cpp
SOURCES += $${WORKSPACE}/libraries/screenshot_creator/screenshot_creator_test.cpp

include(screenshot_creator.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
