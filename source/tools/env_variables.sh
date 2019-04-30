#defines common enviornment variables for all the qt programs
current_dir=$PWD
QMAKE_DIR=~/Qt/5.12.2/gcc_64/bin

#define the abs path of qmake_dir
cd $QMAKE_DIR
QMAKE_DIR=$PWD

#export all variables
export QMAKE_DIR=$QMAKE_DIR

#use source tools/env_variables.sh to import the variables
cd $current_dir
