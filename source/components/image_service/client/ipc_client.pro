QT += core

CONFIG += c++11
#http://doc.qt.io/qt-5/qmake-variable-reference.html

WORKSPACE = $$_PRO_FILE_PWD_/../../../../source

INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp

include(ipc_client.pri)
