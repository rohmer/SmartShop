#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/pigpio.build ]; then
	mkdir /tmp/pigpio.build 
fi
cd /tmp/pigpio.build
cp -R $bdir/pigpio-master/* .
make -j4
make install