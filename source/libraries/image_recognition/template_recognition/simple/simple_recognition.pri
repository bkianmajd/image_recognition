!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

#libraries
LIBS += /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_core.so.3.4 \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so

#include path
INCLUDEPATH +=  $${WORKSPACE}/ \
                $${WORKSPACE}/external_libraries/opencv-3.4.1/include

HEADERS += $${WORKSPACE}/libraries/image_recognition/template_recognition/simple/simple_recognition.h

SOURCES += $${WORKSPACE}/libraries/image_recognition/template_recognition/simple/simple_recognition.cpp

include($${WORKSPACE}/libraries/image_recognition/template_recognition/template_recognition.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/helpers/helpers.pri)

}
