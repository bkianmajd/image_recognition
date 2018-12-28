!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

QT += core
QT += network

HEADERS += $${WORKSPACE}/libraries/postal_service/ipost_card.h
HEADERS += $${WORKSPACE}/libraries/postal_service/postal_service.h

SOURCES += $${WORKSPACE}/libraries/postal_service/postal_service.cpp

INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

include($${WORKSPACE}/external_libraries/protobuf_output/protobuf_output.pri)
include($${WORKSPACE}/libraries/postal_service/com_layer/com_layer.pri)
include($${WORKSPACE}/libraries/postal_service/com_layer/server/server.pri)
include($${WORKSPACE}/libraries/postal_service/com_layer/client/client.pri)

}
