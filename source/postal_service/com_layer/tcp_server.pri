QT += core
QT += network

HEADERS += $${WORKSPACE}/postal_service/com_layer/tcp_server.h \
           $${WORKSPACE}/postal_service/com_layer/icarrier.h

SOURCES += $${WORKSPACE}/postal_service/com_layer/tcp_server.cpp

INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a
