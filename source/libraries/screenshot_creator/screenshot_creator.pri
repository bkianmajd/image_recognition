!contains(included_modules, $$PWD ) {
included_modules += $$PWD
QT += widgets
QT += gui

HEADERS += $${WORKSPACE}/libraries/screenshot_creator/screenshot_creator.h

SOURCES += $${WORKSPACE}/libraries/screenshot_creator/screenshot_creator.cpp

include($${WORKSPACE}/helpers/helpers.pri)
}
