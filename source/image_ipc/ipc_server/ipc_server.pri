HEADERS += $${WORKSPACE}/image_ipc/ipc_server/image_command_distributor.h
HEADERS += $${WORKSPACE}/image_ipc/ipc_server/command_queue.h

SOURCES += $${WORKSPACE}/image_ipc/ipc_server/image_command_distributor.cpp
SOURCES += $${WORKSPACE}/image_ipc/ipc_server/command_queue.cpp

include($${WORKSPACE}/schema/proto_schema.pri)
