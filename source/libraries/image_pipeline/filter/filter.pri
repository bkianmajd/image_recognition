!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/image_pipeline/filter/noise_reducer.h

SOURCES += $${WORKSPACE}/libraries/image_pipeline/filter/noise_reducer.cpp

LIBS += /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_core.so.3.4 \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so

include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/libraries/image_def/utility/utility.pri)
}
