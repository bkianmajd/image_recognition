QT += core
QT += network

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../../source
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/carrier_mock.h

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/libraries/postal_service/com_layer/carrier_test.cpp

include($${WORKSPACE}/libraries/postal_service/com_layer/com_layer.pri)
