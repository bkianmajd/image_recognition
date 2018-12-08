qmake_dir="/home/babak/Qt5.7.0/5.7/gcc_64/bin"
abs_build_dir="$PWD/../../../build"
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

  #compiling
  $qmake_dir/qmake -o $abs_build_dir $abs_path

  # making the file
  cd $abs_build_dir
  make -s

done

#-----running the unit tests----------
for i in $(find . -name '*_test')
do
  ./$i
   
  #echo "=========================="
  #echo "=========================="
done
