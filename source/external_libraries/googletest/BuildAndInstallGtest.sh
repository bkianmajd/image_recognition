#! /bin/bash

#==========================================
# Script to build and install Gtest.
# Run build inside the source directory
#==========================================

# Define variables
GTEST_DIR=$(pwd)
LIB1=/usr/local/lib/libgtest.a
LIB2=/usr/local/lib/libgtest_main.a
INC=/usr/local/include/gtest
BLDDIR=build-aux

# Build/Install only if it doesn't exist
if [[ -f $LIB1 ]] && \
    [[ -f $LIB2 ]] && \
    [[ -d $INC ]]
then
    echo "Looks like gtest is already installed."
    echo "Exiting script..."
    rm -rf $BLDDIR
    exit 0
else
    if [ ! -d $BLDDIR ]; then
        mkdir $BLDDIR
    fi

    cd $BLDDIR
    cmake $GTEST_DIR
    make
    if sudo make install; then
        echo "Install complete."
        exit 0
	rm -rf $BLDDIR
    else
        echo "Install failed."
        echo "Run this script with sudo or as root."
        exit 1
    fi
fi

cd $GTEST_DIR
