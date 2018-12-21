!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/image_service/client/ipc_client.h

SOURCES += $${WORKSPACE}/components/image_service/client/ipc_client.cpp

include($${WORKSPACE}/libraries/postal_service/postal_service.pri)
include($${WORKSPACE}/libraries/postal_service/utility/utility.pri)
include($${WORKSPACE}/schema/proto_schema.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)

}
