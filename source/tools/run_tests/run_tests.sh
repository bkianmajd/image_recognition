qmake_dir="/home/babak/Qt5.7.0/5.7/gcc_64/bin"
build_dir="/home/babak/Desktop/image_recognition/build"
source_dir="$PWD/../.."

cd $source_dir
#pro_files=$(find . -name '*test.pro') 
#pro_files=(*test.pro)
#echo $pro_files

#./qmake output_directory pro_test_files
#$qmake_dir/qmake -o $build_dir $pro_files



for i in $(find . -name '*test.pro')
do
  echo $i
done
