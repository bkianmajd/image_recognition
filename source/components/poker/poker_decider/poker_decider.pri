!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/poker_decider/poker_decider_interface.h

include($${WORKSPACE}/components/poker/entities/entities.pri)
}
