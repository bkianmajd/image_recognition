current_dir=$PWD
build_dir=$PWD/build
source_dir=$PWD/../opencv-3.4.1

source ../../tools/env_variables.sh

# make the build folder
mkdir build

#run cmake
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=$PWD $source_dir
make
