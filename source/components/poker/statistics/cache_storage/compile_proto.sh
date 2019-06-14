WORKSPACE=$PWD/../../../..
OUT_DIR=components/poker/statistics/cache_storage/proto

cd $WORKSPACE
#Generate protobufs relative to workspace - the protobuf input is then specified relative to workspace, and the output automatically mirrors the proto file
$WORKSPACE/external_libraries/protobuf_output/build/bin/protoc --cpp_out=. --proto_path=. ${OUT_DIR}/*.proto

