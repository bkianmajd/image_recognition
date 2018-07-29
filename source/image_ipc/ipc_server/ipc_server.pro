QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = ../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}image_ipc/ipc_server/image_command_distributor_test.cpp
SOURCES += $${WORKSPACE}image_ipc/ipc_server/command_queue_test.cpp


include(ipc_server.pri)
