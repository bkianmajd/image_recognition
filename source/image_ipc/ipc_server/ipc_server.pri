#include path
INCLUDEPATH +=  $${WORKSPACE}

# IPC Server
HEADERS += $${WORKSPACE}/image_ipc/ipc_server/ipc_server.h

SOURCES += $${WORKSPACE}/image_ipc/ipc_server/ipc_server.cpp

LIBS += /usr/local/lib/libprotobuf.a \
/usr/local/lib/libprotoc.a \
/usr/local/lib/libprotobuf-lite.a

include($${WORKSPACE}/com_layer/tcp_server.pri);
