!contains(included_modules, $$PWD ) {
  
  included_modules += $$PWD
  HEADERS += $${WORKSPACE}/libraries/protobuf_loader/protobuf_loader.h
  HEADERS += $${WORKSPACE}/libraries/protobuf_loader/cache_manager.h

  SOURCES += $${WORKSPACE}/libraries/protobuf_loader/protobuf_loader.cpp

  include($$WORKSPACE/external_libraries/protobuf_output/protobuf_output.pri)
  include($$WORKSPACE/helpers/helpers.pri)
  include($$WORKSPACE/schema/proto_schema.pri)
  include($$WORKSPACE/external_libraries/libchrome_output/libchrome_output.pri)
}
