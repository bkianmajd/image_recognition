QT += core
QT += network

HEADERS += $${WORKSPACE}/com_layer/tcp_server.h

SOURCES += $${WORKSPACE}/com_layer/tcp_server.cpp

INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a
