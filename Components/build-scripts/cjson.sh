#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/cjson.build ]; then
	mkdir /tmp/cjson.build
fi
cd /tmp/cjson.build
cp -R $bdir/cJSON-master .
make -j4 
make install

rm -rf /tmp/cjson.build