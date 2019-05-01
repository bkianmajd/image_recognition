current_dir=$PWD
build_dir=$PWD/build
source_dir=$PWD/../protobuf-3.5.x

source ../../tools/env_variables.sh

# make the build folder
mkdir build

#run make
cd $source_dir
chmod +x autogen.sh
./autogen.sh
./configure --prefix=$build_dir
make
make install
