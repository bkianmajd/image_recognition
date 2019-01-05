!contains(included_modules, $$PWD ) {
  included_modules += $$PWD


HEADERS += $${WORKSPACE}/libraries/image_recognition/image_recognition_api.h
HEADERS += $${WORKSPACE}/libraries/image_recognition/image_recognition_defs.h

SOURCES += $${WORKSPACE}/libraries/image_recognition/image_recognition_api.cpp
SOURCES += $${WORKSPACE}/libraries/image_recognition/image_recognition_defs.cpp

include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/helpers/helpers.pri)

# Feature dependencies
include($${WORKSPACE}/libraries/image_file_manager/image_file_manager.pri)
include($${WORKSPACE}/libraries/image_uploader/image_uploader.pri)
include($${WORKSPACE}/libraries/image_recognition/template_recognition/template_recognition.pri)
include($${WORKSPACE}/libraries/image_recognition/template_recognition/simple/simple_recognition.pri)
include($${WORKSPACE}/libraries/image_recognition/template_converter/template_converter.pri)
}
