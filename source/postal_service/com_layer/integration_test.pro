QT += core
QT += network

CONFIG += c++11

WORKSPACE = ../../../source
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/postal_service/com_layer/integration_test.cpp

include(tcp_server.pri)
include(tcp_client.pri)