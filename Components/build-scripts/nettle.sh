#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/nettle.build ]; then
	mkdir /tmp/nettle.build
fi
cd /tmp/nettle.build
/bin/bash $bdir/WebServer/nettle-3.8/configure --disable-documentation
make -j4 
make install
rm -rf /tmp/nettle.build