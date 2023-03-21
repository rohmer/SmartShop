#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/oatpp.build ]; then
	mkdir /tmp/oatpp.build 
fi
cd /tmp/oatpp.build

cmake $bdir/oatpp-master
make -j4
cp src/liboatpp.so /usr/local/lib