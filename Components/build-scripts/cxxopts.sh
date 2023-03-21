#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/cxxopts.build ]; then
	mkdir /tmp/cxxopts.build
fi
cd /tmp/cxxopts.build
cmake $bdir/cxxopts-master
make -j4 
make install

rm -rf /tmp/cxxopts.build