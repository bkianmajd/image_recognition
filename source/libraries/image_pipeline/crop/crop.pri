!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/image_pipeline/crop/vertical_crop.h

SOURCES += $${WORKSPACE}/libraries/image_pipeline/crop/vertical_crop.cpp

include($${WORKSPACE}/libraries/image_def/utility/utility.pri)
include($${WORKSPACE}/external_libraries/opencv_output/opencv_output.pri)
}
