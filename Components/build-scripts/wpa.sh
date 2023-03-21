#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/wpa.build ]; then
	mkdir /tmp/wpa.build
fi
cd /tmp/wpa.build

cmake $bdir/libwpa
cp libwpa.so /usr/local/lib
