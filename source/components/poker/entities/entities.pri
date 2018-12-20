!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/entities/card_def.h
HEADERS += $${WORKSPACE}/components/poker/entities/player_health_def.h
HEADERS += $${WORKSPACE}/components/poker/entities/poker_model_def.h
HEADERS += $${WORKSPACE}/components/poker/entities/player_location_def.h

SOURCES += $${WORKSPACE}/components/poker/entities/card_def.cpp
}
