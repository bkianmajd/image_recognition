!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/image_service/server/ipc_server.h

SOURCES += $${WORKSPACE}/components/image_service/server/ipc_server.cpp

include($${WORKSPACE}/libraries/postal_service/postal_service.pri)
include($${WORKSPACE}/libraries/screenshot_creator/screenshot_creator.pri)
include($${WORKSPACE}/libraries/postal_service/utility/utility.pri)
include($${WORKSPACE}/schema/proto_schema.pri)

}
