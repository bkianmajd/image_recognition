QT += core
QT += network

CONFIG += c++11

WORKSPACE = ../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/postal_service/postal_service_test.cpp
SOURCES += $${WORKSPACE}/postal_service/mail_distributor_simple/mail_distributor_simple.cpp


include($${WORKSPACE}/postal_service/postal_service.pri)
include($${WORKSPACE}/postal_service/post_cards/post_cards.pri)
