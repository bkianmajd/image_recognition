QT += core
QT -= gui

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../source/
INCLUDEPATH += $${WORKSPACE}
include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/libraries/protobuf_loader/protobuf_loader_test.cpp

include($${WORKSPACE}/libraries/protobuf_loader/protobuf_loader.pri)
