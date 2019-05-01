QT += core
QT -= gui

CONFIG += c++14

WORKSPACE = $$_PRO_FILE_PWD_/../../../source/
INCLUDEPATH += $${WORKSPACE}


include($${WORKSPACE}/external_libraries/googletest_output/googletest_output.pri)

SOURCES += $${WORKSPACE}/google_test/widget_main.cpp
SOURCES += $${WORKSPACE}/components/poker/poker_workflow_test.cpp
SOURCES += $${WORKSPACE}/components/poker/workflow_session_thread_test.cpp

include(poker_workflow.pri)
