!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/nueral_net/defs/nueral_net_defs.h

include($${WORKSPACE}/external_libraries/eigen_output/eigen_output.pri)
}
