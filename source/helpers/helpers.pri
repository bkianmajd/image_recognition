!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

  HEADERS += $${WORKSPACE}/helpers/directory_finder.h
  HEADERS += $${WORKSPACE}/helpers/compare.h

  SOURCES += $${WORKSPACE}/helpers/directory_finder.cpp
  SOURCES += $${WORKSPACE}/helpers/compare.cpp
}



