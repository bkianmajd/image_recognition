!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/statistics/winning_calculator/winning_calculator.h

SOURCES += $${WORKSPACE}/components/poker/statistics/winning_calculator/winning_calculator.cpp

include($${WORKSPACE}/components/poker/statistics/brute_force_generator/brute_force_generator.pri)
include($${WORKSPACE}/components/poker/statistics/winning_calculator/cache_manager/cache_manager.pri)
}
