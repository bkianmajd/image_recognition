!contains(included_modules, $$PWD ) {
  included_modules += $$PWD


HEADERS += $${WORKSPACE}/libraries/image_file_manager/image_file_manager.h
HEADERS += $${WORKSPACE}/libraries/image_file_manager/image_file_manager_interface.h
HEADERS += $${WORKSPACE}/libraries/image_file_manager/image_file_manager_mock.hpp

SOURCES += $${WORKSPACE}/libraries/image_file_manager/image_file_manager.cpp

include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/helpers/helpers.pri)

}
