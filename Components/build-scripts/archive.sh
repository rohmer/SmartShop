#!/bin/bash

bdir=$(pwd)

if [ ! -d /tmp/archive.build ]; then
	mkdir /tmp/archive.build
fi
cd /tmp/archive.build
cmake $bdir/libarchive-3.6.2
make -j4
make install

rm -rf /tmp/archive.build