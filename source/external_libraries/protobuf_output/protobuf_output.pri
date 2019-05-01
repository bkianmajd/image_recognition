!contains(included_modules, $$PWD ) {
included_modules += $$PWD

  INCLUDEPATH += $${WORKSPACE}/external_libraries/protobuf_output/build/include
  win32 {
  }

  !win32 {
    LIBS += $${WORKSPACE}/external_libraries/protobuf_output/build/lib/libprotobuf.a
  }
}
