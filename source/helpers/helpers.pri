!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

  HEADERS += $${WORKSPACE}/helpers/directory_finder.h

  SOURCES += $${WORKSPACE}/helpers/directory_finder.cpp
}



