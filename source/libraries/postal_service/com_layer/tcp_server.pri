!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

QT += core
QT += network

HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/tcp_server.h
HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/icarrier.h

SOURCES += $${WORKSPACE}/libraries/postal_service/com_layer/tcp_server.cpp

INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

}
