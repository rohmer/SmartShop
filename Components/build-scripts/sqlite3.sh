#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/sqlite3.build ]; then
	mkdir /tmp/sqlite3.build 
fi
cd /tmp/sqlite3.build
cp -R $bdir/sqlite3/* .
./configure
make -j4
make install