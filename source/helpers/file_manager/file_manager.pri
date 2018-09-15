!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

  HEADERS += $${WORKSPACE}/helpers/file_manager/file_manager.h

  SOURCES += $${WORKSPACE}/helpers/file_manager/file_manager.cpp

  include($${WORKSPACE}/helpers/helpers.pri)
}

