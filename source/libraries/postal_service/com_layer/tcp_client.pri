!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/tcp_client.h
HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/com_defs.h

SOURCES += $${WORKSPACE}/libraries/postal_service/com_layer/tcp_client.cpp

INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

}
