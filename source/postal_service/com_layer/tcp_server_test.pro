QT += core
QT += network

CONFIG += c++11

WORKSPACE = ../../../source
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp \
           $${WORKSPACE}/postal_service/com_layer/tcp_server_test.cpp

include(tcp_server.pri)