HEADERS += $${WORKSPACE}/image_ipc/ipc_server/image_command_creator.h
HEADERS += $${WORKSPACE}/image_ipc/ipc_server/ipc_server_controller.h
HEADERS += $${WORKSPACE}/image_ipc/ipc_server/image_command_dispatcher.h

SOURCES += $${WORKSPACE}/image_ipc/ipc_server/image_command_creator.cpp
SOURCES += $${WORKSPACE}/image_ipc/ipc_server/ipc_server_controller.cpp
SOURCES += $${WORKSPACE}/image_ipc/ipc_server/image_command_dispatcher.cpp

include($${WORKSPACE}/postal_service/postal_service.pri)
include($${WORKSPACE}/postal_service/utility/utility.pri)
include($${WORKSPACE}/schema/proto_schema.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/template_recognition/template_recognition.pri)
