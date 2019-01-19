!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/libraries/session_thread/session_thread.h


include($${WORKSPACE}/external_libraries/libchrome_output/libchrome_output.pri)
}
