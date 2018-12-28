!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

QT += core
QT += network

HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/server/tcp_server.h

SOURCES += $${WORKSPACE}/libraries/postal_service/com_layer/server/tcp_server.cpp

include($${WORKSPACE}/libraries/postal_service/com_layer/com_layer.pri)
}
