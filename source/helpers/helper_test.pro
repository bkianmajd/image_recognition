QT += core

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../source/
INCLUDEPATH += $${WORKSPACE}

include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/helpers/helper_testers.cpp

include(helpers.pri)
