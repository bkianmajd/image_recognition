QT += core
QT += network

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../source
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp \
           $${WORKSPACE}/libraries/postal_service/com_layer/server/tcp_server_test.cpp

include($${WORKSPACE}/libraries/postal_service/com_layer/server/server.pri)