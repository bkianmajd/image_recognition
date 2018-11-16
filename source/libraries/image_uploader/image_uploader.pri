!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

  HEADERS += $${WORKSPACE}/libraries/image_uploader/image_uploader.h
  HEADERS += $${WORKSPACE}/libraries/image_file_manager/image_file_manager.h

  SOURCES += $${WORKSPACE}/libraries/image_uploader/image_uploader.cpp

include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/helpers/helpers.pri)
}
