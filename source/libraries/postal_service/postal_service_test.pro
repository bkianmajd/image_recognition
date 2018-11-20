QT += core
QT += network

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/libraries/postal_service/postal_service_test.cpp


include($${WORKSPACE}/libraries/postal_service/postal_service.pri)
include($${WORKSPACE}/libraries/postal_service/utility/utility.pri)
include($${WORKSPACE}/schema/proto_schema.pri)
