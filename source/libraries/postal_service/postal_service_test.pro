QT += core
QT += network

CONFIG += c++11
CONFIG += warn_off

WORKSPACE = $$_PRO_FILE_PWD_/../../../source/
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/libraries/postal_service/postal_service_test.cpp


include($${WORKSPACE}/libraries/postal_service/postal_service.pri)
include($${WORKSPACE}/libraries/postal_service/utility/utility.pri)
include($${WORKSPACE}/schema/proto_schema.pri)
