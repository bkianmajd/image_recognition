QT += core

CONFIG += c++11
CONFIG += console
#http://doc.qt.io/qt-5/qmake-variable-reference.html

WORKSPACE = $$_PRO_FILE_PWD_/../../../source
message($${WORKSPACE})

INCLUDEPATH += $${WORKSPACE}

HEADERS += $${WORKSPACE}/executable/ipc_server_runner/static_config.h
SOURCES += $${WORKSPACE}/executable/ipc_server_runner/ipc_server_runner.cpp

include($${WORKSPACE}/image_ipc/ipc_server/ipc_server.pri)
