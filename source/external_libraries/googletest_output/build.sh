current_dir=$PWD
build_dir=$PWD/build
source_dir=$PWD/../googletest

source ../../tools/env_variables.sh

# make the build folder
mkdir build

#run cmake
cd build
cmake $source_dir
make
