!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/simulator/defs/game_moderator.h
HEADERS += $${WORKSPACE}/components/poker/simulator/defs/point_calculator.h

SOURCES += $${WORKSPACE}/components/poker/simulator/defs/game_moderator.cpp
SOURCES += $${WORKSPACE}/components/poker/simulator/defs/point_calculator.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
}
