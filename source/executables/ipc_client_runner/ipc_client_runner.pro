QT += core

CONFIG += c++11
CONFIG += console
#http://doc.qt.io/qt-5/qmake-variable-reference.html

WORKSPACE = $$_PRO_FILE_PWD_/../../../source

INCLUDEPATH += $${WORKSPACE}

HEADERS += $${WORKSPACE}/executables/ipc_client_runner/static_config.h
SOURCES += $${WORKSPACE}/executables/ipc_client_runner/ipc_client_runner.cpp
include($${WORKSPACE}/components/image_service/client/ipc_client.pri)
