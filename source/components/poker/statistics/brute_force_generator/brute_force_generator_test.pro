QT += core
QT -= gui

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../source/
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/components/poker/statistics/brute_force_generator/hand_generator_test.cpp
SOURCES += $${WORKSPACE}/components/poker/statistics/brute_force_generator/table_generator_test.cpp


include($${WORKSPACE}/components/poker/statistics/brute_force_generator/brute_force_generator.pri)
