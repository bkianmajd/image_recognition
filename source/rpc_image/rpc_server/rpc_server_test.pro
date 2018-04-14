QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = ../../../source/
INCLUDEPATH +=  $${WORKSPACE}
INCLUDEPATH +=  $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp \
           $${WORKSPACE}/rpc_image/rpc_server/rpc_server_test.cpp

include(rpc_server.pri)
