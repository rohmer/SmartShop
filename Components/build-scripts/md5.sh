#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/md5.build ]; then
	mkdir /tmp/md5.build 
fi
cd /tmp/md5.build

cmake $bdir/md5-master
make 
cp libmd5.so /usr/local/lib
cp $bdir/md5-master/md5.h /usr/local/include
