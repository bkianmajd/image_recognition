!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/pipeline/pipeline.h

SOURCES += $${WORKSPACE}/libraries/pipeline/pipeline.cpp

include($${WORKSPACE}/libraries/pipeline/utility/utility.pri)
include($${WORKSPACE}/libraries/pipeline/filter/filter.pri)
include($${WORKSPACE}/libraries/pipeline/crop/crop.pri)
}
