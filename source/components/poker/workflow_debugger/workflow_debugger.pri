!contains(included_modules, $$PWD ) {
included_modules += $$PWD
HEADERS += $${WORKSPACE}/components/poker/workflow_debugger/workflow_debugger.h
HEADERS += $${WORKSPACE}/components/poker/workflow_debugger/workflow_debugger_interface.h
HEADERS += $${WORKSPACE}/components/poker/workflow_debugger/workflow_debugger_mock.h


SOURCES += $${WORKSPACE}/components/poker/workflow_debugger/workflow_debugger.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
}
