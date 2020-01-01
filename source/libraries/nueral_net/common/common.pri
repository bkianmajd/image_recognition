!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/libraries/nueral_net/common/sigmoid.h
HEADERS += $${WORKSPACE}/libraries/nueral_net/common/theta_creator.h
HEADERS += $${WORKSPACE}/libraries/nueral_net/common/layer.h
HEADERS += $${WORKSPACE}/libraries/nueral_net/common/data_point_solver.h

SOURCES += $${WORKSPACE}/libraries/nueral_net/common/sigmoid.cpp

include($${WORKSPACE}/libraries/nueral_net/defs/defs.pri)
include($${WORKSPACE}/external_libraries/eigen_output/eigen_output.pri)
include($${WORKSPACE}/helpers/helpers.pri)
}
