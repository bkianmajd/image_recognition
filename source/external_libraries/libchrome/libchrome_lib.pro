TARGET = chrome_output
TEMPLATE = lib
CONFIG += c++14
CONFIG += staticlib

WORKSPACE = $$_PRO_FILE_PWD_/../../../source/
INCLUDEPATH += $${WORKSPACE}

target.path = $${WORKSPACE}/external_libraries/libchrome_output
INSTALLS += target


LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

include($${WORKSPACE}/external_libraries/libchrome/libchrome.pri)
