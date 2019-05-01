!contains(included_modules, $$PWD ) {
included_modules += $$PWD
  LIBS += $${WORKSPACE}/external_libraries/googletest_output/build/libgtest.a

  INCLUDEPATH += $${WORKSPACE}/external_libraries/googletest/include
}
