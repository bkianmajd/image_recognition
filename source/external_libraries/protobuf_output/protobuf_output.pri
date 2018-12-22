!contains(included_modules, $$PWD ) {
included_modules += $$PWD

  win32 {
    LIBS += $${WORKSPACE}/external_libraries/protobuf_output/libprotobufd.lib
  }

  !win32 {
    LIBS += /usr/local/lib/libprotobuf.a
  }
}
