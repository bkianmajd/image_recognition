!contains(included_modules, $$PWD ) {
included_modules += $$PWD

#system(protoc --proto_path=$${WORKSPACE}/components/poker/statistics/winning_calculator/cache_manager \
#              --cpp_out=$${WORKSPACE}/components/poker/statistics/winning_calculator/cache_manager/compiled_files/. \
#              poker_statistics.proto)

#auto generated proto files
HEADERS += $${WORKSPACE}/components/poker/statistics/cache_manager/proto/poker_statistics.pb.h
SOURCES += $${WORKSPACE}/components/poker/statistics/cache_manager/proto/poker_statistics.pb.cc


HEADERS += $${WORKSPACE}/components/poker/statistics/cache_manager/cache_manager.h
SOURCES += $${WORKSPACE}/components/poker/statistics/cache_manager/cache_manager.cpp

include($${WORKSPACE}/external_libraries/protobuf_output/protobuf_output.pri)
include($${WORKSPACE}/external_libraries/libchrome_output/libchrome_output.pri)
include($${WORKSPACE}/helpers/helpers.pri)
include($${WORKSPACE}/libraries/protobuf_loader/protobuf_loader.pri)
include($${WORKSPACE}/components/poker/entities/entities.pri)
}
