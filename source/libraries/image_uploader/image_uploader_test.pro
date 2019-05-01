QT += core
QT += network

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../source/
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/libraries/image_uploader/image_uploader_test.cpp
SOURCES += $${WORKSPACE}/google_test/main.cpp

include($${WORKSPACE}/libraries/image_uploader/image_uploader.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/helpers/helpers.pri)
