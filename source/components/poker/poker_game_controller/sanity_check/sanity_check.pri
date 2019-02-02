!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/sanity_check/sanity_checker.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/sanity_check/sanity_checker.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
include($${WORKSPACE}/components/poker/entities/comparator/comparator.pri)
}
