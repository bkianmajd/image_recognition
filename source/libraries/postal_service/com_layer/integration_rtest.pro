QT += core
QT += network

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../../source
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/libraries/postal_service/com_layer/integration_test.cpp

include($${WORKSPACE}/libraries/postal_service/com_layer/com_layer.pri)
include($${WORKSPACE}/libraries/postal_service/com_layer/server/server.pri)
include($${WORKSPACE}/libraries/postal_service/com_layer/client/client.pri)
