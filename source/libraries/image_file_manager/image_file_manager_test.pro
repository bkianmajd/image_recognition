QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../source
INCLUDEPATH +=  $${WORKSPACE}
INCLUDEPATH +=  $${WORKSPACE}/external_libraries/googletest/include

include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/google_test/main.cpp \
           $${WORKSPACE}/libraries/image_file_manager/image_file_manager_test.cpp

include($${WORKSPACE}/libraries/image_file_manager/image_file_manager.pri)
