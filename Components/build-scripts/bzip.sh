#!/bin/bash

apt install liblz4-dev libzstd-dev libacl1-dev -y

bdir=$(pwd)
if [ ! -d /tmp/bzip2.build ]; then
	mkdir /tmp/bzip2.build
fi
cd /tmp/bzip2.build
cp -R $bdir/bzip2-1.0.8/* .
make -j4 -f Makefile-libbz2_so
make install

rm -rf /tmp/bzip2.build