#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/uuid.build ]; then
	mkdir /tmp/uuid.build
fi
cd /tmp/uuid.build
cp -R $bdir/libuuid-master/* .
bash ./configure
make -j4
make install

rm -rf /tmp/uuid.build