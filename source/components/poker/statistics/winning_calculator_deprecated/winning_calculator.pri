!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/statistics/winning_calculator/winning_calculator.h
HEADERS += $${WORKSPACE}/components/poker/statistics/winning_calculator/losing_probability_counter.h

SOURCES += $${WORKSPACE}/components/poker/statistics/winning_calculator/winning_calculator.cpp

include($${WORKSPACE}/components/poker/statistics/brute_force_generator/brute_force_generator.pri)
include($${WORKSPACE}/components/poker/statistics/cache_manager/cache_manager.pri)
include($${WORKSPACE}/components/poker/simulator/defs/defs.pri)
include($${WORKSPACE}/libraries/protobuf_loader/protobuf_loader.pri)

}
