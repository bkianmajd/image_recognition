!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/poker_decider/simple_decider/simple_decider.h

SOURCES += $${WORKSPACE}/components/poker/poker_decider/simple_decider/simple_decider.cpp

include($${WORKSPACE}/components/poker/poker_decider/poker_decider.pri)
include($${WORKSPACE}/components/poker/statistics/hand_calculator/hand_calculator.pri)
}
