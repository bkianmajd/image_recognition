QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = ../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}libraries/template_converter/template_converter_test.cpp

include(template_converter.pri)