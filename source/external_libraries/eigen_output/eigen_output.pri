!contains(included_modules, $$PWD ) {
included_modules += $$PWD
  INCLUDEPATH += $${WORKSPACE}/external_libraries/eigen_output/build/include
}
