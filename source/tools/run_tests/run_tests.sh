source ../env_variables.sh
build_dir="$PWD/../../../build"
source_dir="$PWD/../.."

cd $build_dir
mkdir testing_cache
abs_build_dir="$build_dir/testing_cache"
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
  $QMAKE_DIR/qmake -o $abs_build_dir $abs_path

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
