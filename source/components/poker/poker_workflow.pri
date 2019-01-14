!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/poker_workflow.h
HEADERS += $${WORKSPACE}/components/poker/workflow_session_thread.h
HEADERS += $${WORKSPACE}/components/poker/workflow_session.h

SOURCES += $${WORKSPACE}/components/poker/poker_workflow.cpp
SOURCES += $${WORKSPACE}/components/poker/workflow_session_thread.cpp
SOURCES += $${WORKSPACE}/components/poker/workflow_session.cpp

include($${WORKSPACE}/components/poker/entities/entities.pri)
include($${WORKSPACE}/components/poker/poker_game_controller/poker_game_controller.pri)
include($${WORKSPACE}/components/poker/poker_game_controller/training/training.pri)
include($${WORKSPACE}/external_libraries/libchrome_output/libchrome_output.pri)
}
