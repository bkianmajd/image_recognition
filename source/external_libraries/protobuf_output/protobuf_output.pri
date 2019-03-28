!contains(included_modules, $$PWD ) {
included_modules += $$PWD

  INCLUDEPATH += $${WORKSPACE}/external_libraries/protobuf-3.5.x/src
  win32 {
  }

  !win32 {
    LIBS += $${WORKSPACE}/external_libraries/protobuf_output/build/libprotobuf.a
  }
}
