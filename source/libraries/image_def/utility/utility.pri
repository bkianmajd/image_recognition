!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/image_def/utility/utility.h

SOURCES += $${WORKSPACE}/libraries/image_def/utility/utility.cpp

include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/external_libraries/opencv_output/opencv_output.pri)
}
