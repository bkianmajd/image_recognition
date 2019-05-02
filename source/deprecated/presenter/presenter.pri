!contains(included_modules, $$PWD ) {
  included_modules += $$PWD


HEADERS += $${WORKSPACE}/libraries/image_recognition/template_recognition/template_recognition_interface.h \
           $${WORKSPACE}/libraries/image_recognition/template_recognition/template_recognition_defs.h

HEADERS += $${WORKSPACE}/libraries/image_recognition/template_recognition/template_recognition_manager.h
HEADERS += $${WORKSPACE}/libraries/image_recognition/template_recognition/template_recognition_mock.hpp

include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/helpers/helpers.pri)

}
