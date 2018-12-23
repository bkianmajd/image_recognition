!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

QT += core
QT += network

HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/com_defs.h
HEADERS += $${WORKSPACE}/libraries/postal_service/com_layer/carrier_base.h

SOURCES += $${WORKSPACE}/libraries/postal_service/com_layer/carrier_base.cpp

INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

}
