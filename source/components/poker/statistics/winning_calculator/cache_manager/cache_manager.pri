!contains(included_modules, $$PWD ) {
included_modules += $$PWD

system(protoc --proto_path=$${WORKSPACE}/components/poker/statistics/winning_calculator/cache_manager \
              --cpp_out=$${WORKSPACE}/components/poker/statistics/winning_calculator/cache_manager/compiled_files/. \
              poker_statistics.proto)
#auto generated proto files
HEADERS += $${WORKSPACE}/components/poker/statistics/winning_calculator/cache_manager/compiled_files/poker_statistics.pb.h
SOURCES += $${WORKSPACE}/components/poker/statistics/winning_calculator/cache_manager/compiled_files/poker_statistics.pb.cc


HEADERS += $${WORKSPACE}/components/poker/statistics/winning_calculator/cache_manager/cache_manager.h
SOURCES += $${WORKSPACE}/components/poker/statistics/winning_calculator/cache_manager/cache_manager.cpp
}
