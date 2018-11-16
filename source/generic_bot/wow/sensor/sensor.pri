HEADERS += $${WORKSPACE}/generic_bot/idetector.h
HEADERS += $${WORKSPACE}/generic_bot/wow/sensor/sensor_manager.h
HEADERS += $${WORKSPACE}/generic_bot/wow/sensor/sensor_def.h
HEADERS += $${WORKSPACE}/generic_bot/wow/sensor/wow_detectors/generic_detector.h
HEADERS += $${WORKSPACE}/generic_bot/wow/sensor/wow_object_detector_factory.h

SOURCES += $${WORKSPACE}/generic_bot/wow/sensor/sensor_manager.cpp
SOURCES += $${WORKSPACE}/generic_bot/wow/sensor/wow_detectors/generic_detector.cpp
SOURCES += $${WORKSPACE}/generic_bot/wow/sensor/wow_object_detector_factory.cpp

include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/template_recognition/template_recognition.pri)
