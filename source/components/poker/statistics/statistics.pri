!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/statistics/statistic_calculator.h

SOURCES += $${WORKSPACE}/components/poker/statistics/statistic_calculator.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
}
