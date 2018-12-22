!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

HEADERS += $${WORKSPACE}/schema/compiled_files/*.h

SOURCES += $${WORKSPACE}/schema/compiled_files/*.cc

INCLUDEPATH += $${WORKSPACE}/external_libraries/protobuf/src

include($${WORKSPACE}/external_libraries/protobuf_output/protobuf_output.pri)
}

