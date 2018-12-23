!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

QT += core
QT += network

HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/client/tcp_client.h
HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/com_defs.h

SOURCES += $${WORKSPACE}/libraries/postal_service/com_layer/client/tcp_client.cpp

INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

}
