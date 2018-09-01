HEADERS += $${WORKSPACE}/image_ipc/ipc_server/image_command_distributor.h
HEADERS += $${WORKSPACE}/image_ipc/ipc_server/ipc_server_controller.h

SOURCES += $${WORKSPACE}/image_ipc/ipc_server/image_command_distributor.cpp
SOURCES += $${WORKSPACE}/image_ipc/ipc_server/ipc_server_controller.cpp

include($${WORKSPACE}/postal_service/postal_service.pri)
include($${WORKSPACE}/postal_service/utility/utility.pri)
include($${WORKSPACE}/schema/proto_schema.pri)
include($${WORKSPACE}/image_ipc/file_manager/file_manager.pri)
