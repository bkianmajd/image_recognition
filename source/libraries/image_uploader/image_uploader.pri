!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

  HEADERS += $${WORKSPACE}/libraries/image_uploader/image_uploader.h
  HEADERS += $${WORKSPACE}/libraries/image_file_manager/image_file_manager.h

  SOURCES += $${WORKSPACE}/libraries/image_uploader/image_uploader.cpp

include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/external_libraries/opencv_output/opencv_output.pri)
}
