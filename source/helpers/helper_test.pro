QT += core

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/helpers/helper_testers.cpp

include(helpers.pri)
