!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/statistics/statistics_defs.h
HEADERS += $${WORKSPACE}/components/poker/statistics/texas_holdem_calculator.h

SOURCES += $${WORKSPACE}/components/poker/statistics/texas_holdem_calculator.cpp
}
