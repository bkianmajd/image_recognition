QT += core
QT -= gui

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../../source/
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/components/poker/entities/entities_test.cpp
SOURCES += $${WORKSPACE}/components/poker/entities/card_sorter_test.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
