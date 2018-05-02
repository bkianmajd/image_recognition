QT += core
QT += network

HEADERS += $${WORKSPACE}/postal_service/ipost_card.h
HEADERS += $${WORKSPACE}/postal_service/postal_service.h

SOURCES += $${WORKSPACE}/postal_service/postal_service.cpp

INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += /usr/local/lib/libprotobuf.a \
        /usr/local/lib/libprotoc.a \
        /usr/local/lib/libprotobuf-lite.a\
        $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

include($${WORKSPACE}/postal_service/com_layer/tcp_server.pri)
include($${WORKSPACE}/postal_service/com_layer/tcp_client.pri)
