!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/entities/card_def.h
HEADERS += $${WORKSPACE}/components/poker/entities/player_location_def.h
HEADERS += $${WORKSPACE}/components/poker/entities/game_model_def.h
HEADERS += $${WORKSPACE}/components/poker/entities/workflow_model_def.h

SOURCES += $${WORKSPACE}/components/poker/entities/card_def.cpp
}
