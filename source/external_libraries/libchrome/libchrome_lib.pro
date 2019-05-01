TARGET = chrome_output
TEMPLATE = lib
CONFIG += c++14
CONFIG += staticlib

WORKSPACE = $$_PRO_FILE_PWD_/../../../source/
INCLUDEPATH += $${WORKSPACE}

target.path = $${WORKSPACE}/external_libraries/libchrome_output
INSTALLS += target


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

include($${WORKSPACE}/external_libraries/libchrome/libchrome.pri)
