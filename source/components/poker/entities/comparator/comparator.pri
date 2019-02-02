!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/entities/comparator/comparator.h

SOURCES += $${WORKSPACE}/components/poker/entities/comparator/comparator.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
}
