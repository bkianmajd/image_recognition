QT += core
QT -= gui

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

# The main file
SOURCES += $${WORKSPACE}/components/poker/statistics/cache_storage/cache_storage_runner.cpp




include($${WORKSPACE}/components/poker/statistics/cache_storage/cache_storage.pri)

