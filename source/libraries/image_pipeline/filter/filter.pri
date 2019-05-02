!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/image_pipeline/filter/noise_reducer.h

SOURCES += $${WORKSPACE}/libraries/image_pipeline/filter/noise_reducer.cpp

include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/libraries/image_def/utility/utility.pri)
include($${WORKSPACE}/external_libraries/opencv_output/opencv_output.pri)
}
