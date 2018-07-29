#include path
INCLUDEPATH +=  $${WORKSPACE}/ \
                $${WORKSPACE}/external_libraries/opencv-3.4.1/include

HEADERS += $${WORKSPACE}/template_recognition/simple/simple_recognition.h
SOURCES += $${WORKSPACE}/template_recognition/simple/simple_recognition.cpp

include($${WORKSPACE}/template_recognition/template_recognition.pri)
