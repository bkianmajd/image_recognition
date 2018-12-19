!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/model_generator/model_generator.h

SOURCES += $${WORKSPACE}/components/poker/model_generator/model_generator.cpp
}
