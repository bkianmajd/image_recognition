!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

  HEADERS += $${WORKSPACE}/helpers/directory_finder.h
  HEADERS += $${WORKSPACE}/helpers/compare.h
  HEADERS += $${WORKSPACE}/helpers/time_analyzer.h
  HEADERS += $${WORKSPACE}/helpers/file_manager.h

  SOURCES += $${WORKSPACE}/helpers/directory_finder.cpp
  SOURCES += $${WORKSPACE}/helpers/compare.cpp
  SOURCES += $${WORKSPACE}/helpers/time_analyzer.cpp
  SOURCES += $${WORKSPACE}/helpers/file_manager.cpp
}



