QT += core
QT += network

CONFIG += c++11

WORKSPACE = ../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/postal_service/postal_service_test.cpp


include($${WORKSPACE}/postal_service/postal_service.pri)
include($${WORKSPACE}/postal_service/utility/utility.pri)
include($${WORKSPACE}/schema/proto_schema.pri)
