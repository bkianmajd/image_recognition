!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/statistics/brute_force_generator/hand_generator.h

HEADERS += $${WORKSPACE}/components/poker/statistics/brute_force_generator/table_generator.h


SOURCES += $${WORKSPACE}/components/poker/statistics/brute_force_generator/hand_generator.cpp

SOURCES += $${WORKSPACE}/components/poker/statistics/brute_force_generator/table_generator.cpp

include($${WORKSPACE}/components/poker/simulator/simulator.pri)
include($${WORKSPACE}/helpers/helpers.pri)
}
