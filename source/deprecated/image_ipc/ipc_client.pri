HEADERS += $${WORKSPACE}/image_ipc/ipc_client.h

SOURCES += $${WORKSPACE}/image_ipc/ipc_client.cpp

include($${WORKSPACE}/postal_service/postal_service.pri)
include($${WORKSPACE}/postal_service/utility/utility.pri)
include($${WORKSPACE}/schema/proto_schema.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/template_recognition/template_recognition.pri)
