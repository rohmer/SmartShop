#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/wiringx.build ]; then
	mkdir /tmp/wiringx.build
fi
cd /tmp/wiringx.build
cmake $bdir/wiringX-master
make -j4 
make install

rm -rf /tmp/wiringx.build