!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/pipeline/utility/utility.h

SOURCES += $${WORKSPACE}/libraries/pipeline/utility/utility.cpp

LIBS += /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_core.so.3.4 \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so

include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
}
