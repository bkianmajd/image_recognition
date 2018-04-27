QT += core
QT += network

CONFIG += c++11

WORKSPACE = ../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/com_layer/main.cpp

include(tcp_server.pri)
include(tcp_client.pri)
