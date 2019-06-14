!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/statistics/cache_storage/cache_dispatcher.h
HEADERS += $${WORKSPACE}/components/poker/statistics/cache_storage/cache_worker.h
HEADERS += $${WORKSPACE}/components/poker/statistics/cache_storage/preflop_similarities.h

SOURCES += $${WORKSPACE}/components/poker/statistics/cache_storage/cache_dispatcher.cpp
HEADERS += $${WORKSPACE}/components/poker/statistics/cache_storage/cache_worker.cpp

include($${WORKSPACE}/external_libraries/libchrome_output/libchrome_output.pri)
include($${WORKSPACE}/components/poker/statistics/brute_force_generator/brute_force_generator.pri)
include($${WORKSPACE}/components/poker/simulator/defs/defs.pri)
include($${WORKSPACE}/libraries/session_thread/session_thread.pri)
include($${WORKSPACE}/components/poker/statistics/defs/defs.pri)
}
