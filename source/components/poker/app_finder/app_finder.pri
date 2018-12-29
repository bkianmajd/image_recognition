!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/app_finder/app_finder.h

SOURCES += $${WORKSPACE}/components/poker/app_finder/app_finder.cpp

include($${WORKSPACE}/components/image_recognition/image_recognition.pri)
include($${WORKSPACE}/libraries/screenshot_creator/screenshot_creator.pri)
}
