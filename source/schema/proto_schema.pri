!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

HEADERS += $${WORKSPACE}/schema/compiled_files/*.h

SOURCES += $${WORKSPACE}/schema/compiled_files/*.cc

INCLUDEPATH += $${WORKSPACE}/external_libraries/protobuf/src

LIBS += /usr/local/lib/libprotobuf.a \
        /usr/local/lib/libprotoc.a \
        /usr/local/lib/libprotobuf-lite.a

}

