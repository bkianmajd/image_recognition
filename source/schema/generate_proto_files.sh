#sudo ldconfig
#protoc --cpp_out=compiled_files/ *.proto

protoc -I . --grpc_out=compiled_files/ --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` *.proto
protoc -I . --cpp_out=compiled_files/ *.proto
