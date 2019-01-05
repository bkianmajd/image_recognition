QT += core
QT -= gui

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/libraries/pipeline/pipeline_test.cpp

include($${WORKSPACE}/libraries/pipeline/pipeline.pri)