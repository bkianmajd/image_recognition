QT += core
QT += widgets
QT += gui


CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../source/
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/google_test/widget_main.cpp
SOURCES += $${WORKSPACE}/libraries/screenshot_creator/screenshot_creator_test.cpp

include(screenshot_creator.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
