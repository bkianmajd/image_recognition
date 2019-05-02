!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/image_comparer/comparer.h
HEADERS += $${WORKSPACE}/libraries/image_comparer/compare_algorithm.h

SOURCES += $${WORKSPACE}/libraries/image_comparer/comparer.cpp
SOURCES += $${WORKSPACE}/libraries/image_comparer/compare_algorithm.cpp

include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/libraries/image_def/utility/utility.pri)
include($${WORKSPACE}/libraries/image_uploader/image_uploader.pri)
include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/external_libraries/opencv_output/opencv_output.pri)
}
