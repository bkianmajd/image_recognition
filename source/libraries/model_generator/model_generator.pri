!contains(included_modules, $$PWD ) {

HEADERS += $${WORKSPACE}/libraries/model_generator/model_generator_interface.h
HEADERS += $${WORKSPACE}/libraries/model_generator/model_generator_mock.hpp
HEADERS += $${WORKSPACE}/libraries/model_generator/model_generator_def.h

}
