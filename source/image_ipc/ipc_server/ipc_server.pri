HEADERS += $${WORKSPACE}/image_ipc/ipc_server/image_command_distributor.h
HEADERS += $${WORKSPACE}/image_ipc/ipc_server/response_handler.h

SOURCES += $${WORKSPACE}/image_ipc/ipc_server/image_command_distributor.cpp
SOURCES += $${WORKSPACE}/image_ipc/ipc_server/response_handler.cpp

include($${WORKSPACE}/schema/proto_schema.pri)
include($${WORKSPACE}/image_ipc/file_manager/file_manager.pri)
