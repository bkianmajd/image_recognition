!contains(included_modules, $$PWD ) {
  included_modules += $$PWD


HEADERS += $${WORKSPACE}/components/image_recognition/image_recognition_api.h

SOURCES += $${WORKSPACE}/components/image_recognition/image_recognition_api.cpp

include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/helpers/helpers.pri)

# Feature dependencies
include($${WORKSPACE}/libraries/image_file_manager/image_file_manager.pri)
include($${WORKSPACE}/libraries/image_uploader/image_uploader.pri)
include($${WORKSPACE}/libraries/template_recognition/template_recognition.pri)
}
