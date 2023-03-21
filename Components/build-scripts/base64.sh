#!/bin/bash

bdir=$(pwd)

if [ ! -d /tmp/base64.build ]; then
	mkdir /tmp/base64.build 
fi
cd /tmp/base64.build
cmake $bdir/cpp-base64-master
make
cp libcpp-base64.so /usr/local/lib
cp $bdir/cpp-base64-master/base64.h /usr/local/include