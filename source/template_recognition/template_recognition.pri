#libraries
LIBS += /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_core.so.3.4 \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so

#include path
INCLUDEPATH +=  $${WORKSPACE}/ \
                $${WORKSPACE}/external_libraries/opencv-3.4.1/include

HEADERS += $${WORKSPACE}/template_recognition/template_recognition_interface.h \
           $${WORKSPACE}/template_recognition/template_recognition_defs.h
HEADERS += $${WORKSPACE}/template_recognition/simple/simple_recognition.h
HEADERS += $${WORKSPACE}/template_recognition/template_recognition_mock.hpp

SOURCES += $${WORKSPACE}/template_recognition/simple/simple_recognition.cpp

