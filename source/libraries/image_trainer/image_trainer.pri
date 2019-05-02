!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/image_trainer/trainer.h

SOURCES += $${WORKSPACE}/libraries/image_trainer/trainer.cpp

include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/libraries/image_comparer/image_comparer.pri)
}
