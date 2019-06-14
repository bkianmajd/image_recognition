!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/statistics/defs/defs.h


include($${WORKSPACE}/components/poker/entities/entities.pri)
}
