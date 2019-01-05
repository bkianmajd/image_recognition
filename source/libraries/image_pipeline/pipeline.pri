!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/image_pipeline/pipeline.h

SOURCES += $${WORKSPACE}/libraries/image_pipeline/pipeline.cpp

include($${WORKSPACE}/libraries/image_def/utility/utility.pri)
include($${WORKSPACE}/libraries/image_pipeline/filter/filter.pri)
include($${WORKSPACE}/libraries/image_pipeline/crop/crop.pri)
}
