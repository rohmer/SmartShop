#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/sigar.build ]; then
	mkdir /tmp/sigar.build 
fi
cd /tmp/sigar.build
cp -R $bdir/sigar-master/* .

bash ./autogen.sh
bash ./configure
make -j4
make install
