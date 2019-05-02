!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

#libraries
include($${WORKSPACE}/external_libraries/opencv_output/opencv_output.pri)

HEADERS += $${WORKSPACE}/libraries/image_recognition/template_recognition/simple/simple_recognition.h

SOURCES += $${WORKSPACE}/libraries/image_recognition/template_recognition/simple/simple_recognition.cpp

include($${WORKSPACE}/libraries/image_recognition/template_recognition/template_recognition.pri)
include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/libraries/image_def/utility/utility.pri)
}
