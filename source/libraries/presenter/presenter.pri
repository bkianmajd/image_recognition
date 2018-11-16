!contains(included_modules, $$PWD ) {
  included_modules += $$PWD


HEADERS += $${WORKSPACE}/libraries/template_recognition/template_recognition_interface.h \
           $${WORKSPACE}/libraries/template_recognition/template_recognition_defs.h

HEADERS += $${WORKSPACE}/libraries/template_recognition/template_recognition_manager.h
HEADERS += $${WORKSPACE}/libraries/template_recognition/template_recognition_mock.hpp

include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/helpers/helpers.pri)

}
