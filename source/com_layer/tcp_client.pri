HEADERS += $${WORKSPACE}/com_layer/tcp_client.h
HEADERS += $${WORKSPACE}/com_layer/com_defs.h

SOURCES += $${WORKSPACE}/com_layer/tcp_client.cpp

INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a
