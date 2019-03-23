!contains(included_modules, $$PWD ) {
included_modules += $$PWD
  LIBS += $${WORKSPACE}/external_libraries/libchrome_output/build/libchrome_output.a

  INCLUDEPATH += $${WORKSPACE}/external_libraries/libchrome
}
