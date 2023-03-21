#!/bin/bash

bdir=$(pwd)/..

apt install libgnutls28-dev libguntls30 -y
if [ ! -d /tmp/microhttpd.build ]; then
	mkdir /tmp/microhttpd.build
fi
cd /tmp/microhttpd.build
/bin/bash $bdir/WebServer/libmicrohttpd-0.9.75/configure --disable-doc
make -j4
make install
rm -rf /tmp/microhttpd.build