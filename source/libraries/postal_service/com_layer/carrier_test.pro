QT += core
QT += network

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../../source
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/carrier_mock.h

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/libraries/postal_service/com_layer/carrier_test.cpp

include($${WORKSPACE}/libraries/postal_service/com_layer/com_layer.pri)
