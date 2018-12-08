qmake_dir="/home/babak/Qt5.7.0/5.7/gcc_64/bin"
abs_build_dir="$PWD/../../../build"
build_dir="../temp_build"
source_dir="$PWD/../.."

cd $source_dir

#----finding pro_files---------
#pro_files=$(find . -name '*test.pro') 
#echo $pro_files


#-----running qmake------------
#./qmake output_directory pro_test_files
#$qmake_dir/qmake -o $build_dir $pro_files


#-----running ./qmake on all *_test.pro files----------
for i in $(find . -name '*_test.pro')
do
  # echo $i

  #storing the absolute path regardless of current directory  
  abs_path=$source_dir/$i
  echo $abs_path

  # move to the project directory
  cd $(dirname $abs_path)
  #echo $PWD

  #creating the build directory
  mkdir $build_dir
  cd $build_dir
  build_dir=$PWD
  cd $(dirname $abs_path)

  #compiling
  $qmake_dir/qmake -o $build_dir $abs_path

  # making the file
  cd $build_dir
  make -s

  # running the file
  test_file=$(find . -name '*_test')  
  ./$test_file


   #delete the build directory
   cd $(dirname $abs_path)
   rm -rf $build_dir
   
  echo "=========================="
  echo "=========================="
done
