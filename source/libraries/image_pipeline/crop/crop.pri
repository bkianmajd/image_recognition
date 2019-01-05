!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/image_pipeline/crop/vertical_crop.h

SOURCES += $${WORKSPACE}/libraries/image_pipeline/crop/vertical_crop.cpp

LIBS += /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_core.so.3.4 \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so

include($${WORKSPACE}/libraries/image_def/utility/utility.pri)
}
