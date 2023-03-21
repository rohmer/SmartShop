#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/httpserver.build ]; then
	mkdir /tmp/httpserver.build 
fi
cd /tmp/httpserver.build
cp -R $bdir/WebServer/libhttpserver-master/* .


/bin/bash $bdir/WebServer/libhttpserver-master/bootstrap

/bin/bash $bdir/WebServer/libhttpserver-master/configure
make -j4
make install
rm -rf /tmp/microhttpd.build