QT += core

CONFIG += c++14
CONFIG += console
#http://doc.qt.io/qt-5/qmake-variable-reference.html

WORKSPACE = $$_PRO_FILE_PWD_/../../../source
#message($${WORKSPACE})

INCLUDEPATH += $${WORKSPACE}

HEADERS += $${WORKSPACE}/executables/ipc_server_runner/static_config.h
SOURCES += $${WORKSPACE}/executables/ipc_server_runner/ipc_server_runner.cpp

include($${WORKSPACE}/components/image_service/server/ipc_server.pri)
include($${WORKSPACE}/components/poker/poker_workflow.pri)
include($${WORKSPACE}/components/session_manager/app_finder/app_finder.pri)
include($${WORKSPACE}/components/poker/workflow_debugger/workflow_debugger.pri)
include($${WORKSPACE}/components/menu_runner/menu_runner.pri)
include($${WORKSPACE}/components/session_manager/session_manager.pri)
