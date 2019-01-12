TARGET = libchrome
TEMPLATE = lib
CONFIG += c++14
CONFIG += staticlib

WORKSPACE = $$_PRO_FILE_PWD_/../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

include($${WORKSPACE}/external_libraries/libchrome/libchrome.pri)
