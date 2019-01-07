QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../source
INCLUDEPATH +=  $${WORKSPACE}
INCLUDEPATH +=  $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp \
           $${WORKSPACE}/libraries/image_recognition/template_recognition/simple/simple_recognition_test.cpp

include($${WORKSPACE}/libraries/image_recognition/template_recognition/simple/simple_recognition.pri)