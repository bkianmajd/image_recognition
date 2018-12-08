QT += core

CONFIG += c++11
#http://doc.qt.io/qt-5/qmake-variable-reference.html

WORKSPACE = $$_PRO_FILE_PWD_/../../../source
message($${WORKSPACE})

INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/image_ipc/ipc_server/image_command_creator_test.cpp
SOURCES += $${WORKSPACE}/image_ipc/ipc_server/ipc_server_controller_test.cpp
SOURCES += $${WORKSPACE}/image_ipc/ipc_server/image_command_dispatcher_test.cpp

include(ipc_server.pri)
