CURRENT_DIR=$PWD

cd ..
git clone https://gitlab.com/libeigen/eigen.git

cd $CURRENT_DIR
mkdir build
cd ../eigen
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=${CURRENT_DIR}/build ..
make -j 7 install
