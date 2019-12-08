!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/session_manager/session_manager.h

SOURCES += $${WORKSPACE}/components/session_manager/session_manager.cpp

include("$${WORKSPACE}/components/poker/poker_workflow.pri")
include("$${WORKSPACE}/components/image_service/server/ipc_server.pri")
include("$${WORKSPACE}/libraries/session_thread/session_thread.pri")
include("$${WORKSPACE}/external_libraries/libchrome_output/libchrome_output.pri")
include($${WORKSPACE}/components/session_manager/app_finder/app_finder.pri)
}
