QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = ../../../source
INCLUDEPATH +=  $${WORKSPACE}
INCLUDEPATH +=  $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp \
           $${WORKSPACE}/template_recognition/simple/simple_recognition_test.cpp

include(simple_recognition.pri)
