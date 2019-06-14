QT += core
QT -= gui

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

# The main file
SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}/components/poker/statistics/cache_storage/cache_worker_test.cpp
SOURCES += $${WORKSPACE}/components/poker/statistics/cache_storage/preflop_similarities_test.cpp

include($${WORKSPACE}/components/poker/statistics/cache_storage/cache_storage.pri)
include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)
