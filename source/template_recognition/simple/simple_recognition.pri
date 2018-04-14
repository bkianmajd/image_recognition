#include path
INCLUDEPATH +=  $${WORKSPACE}/ \
                $${WORKSPACE}/external_libraries/opencv-3.4.1/include


# Kuka rbd test
HEADERS += $${WORKSPACE}/template_recognition/simple/simple_recognition.h

include($${WORKSPACE}/template_recognition/template_recognition.pri)
