!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/simulator/deck_stack_factory.h

SOURCES += $${WORKSPACE}/components/poker/simulator/deck_stack_factory.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
}
