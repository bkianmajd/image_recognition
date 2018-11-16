QT += core
QT -= gui

CONFIG += c++11

WORKSPACE = $$_PRO_FILE_PWD_/../../../../source/
INCLUDEPATH += $${WORKSPACE}
INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include

LIBS += $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a

SOURCES += $${WORKSPACE}/google_test/main.cpp
SOURCES += $${WORKSPACE}generic_bot/wow/sensor/sensor_test.cpp
SOURCES += $${WORKSPACE}generic_bot/wow/sensor/wow_detectors/player_spell_test.cpp

include(sensor.pri)
