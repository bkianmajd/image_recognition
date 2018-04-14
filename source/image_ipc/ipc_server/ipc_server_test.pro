QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = ../../../source/
INCLUDEPATH +=  $${WORKSPACE}
INCLUDEPATH +=  $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp \
           $${WORKSPACE}/image_ipc/ipc_server/ipc_server_test.cpp

include(ipc_server.pri)
