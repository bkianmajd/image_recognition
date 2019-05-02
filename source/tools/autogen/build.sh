current_dir=$PWD
build_dir=$PWD/build
source_dir=$PWD/src

source ../../tools/env_variables.sh

# make the build folder
mkdir build

#run qmake
abs_path=$source_dir/autogen.pro
echo $abs_path
$QMAKE_DIR/qmake -o $build_dir $abs_path

# run make
cd build
make
