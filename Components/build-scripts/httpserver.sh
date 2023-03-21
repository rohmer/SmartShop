#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/httpserver.build ]; then
	mkdir /tmp/httpserver.build 
fi
cd /tmp/httpserver.build
cp $bdir/WebServer/libhttpserver-master/* .
cp -R $bdir/WebServer/libhttpserver-master/m4 .
cp -R $bdir/WebServer/libhttpserver-master/*.am .
cp $bdir/WebServer/libhttpserver-master/libhttpserver.pc.in .
cp $bdir/WebServer/libhttpserver-master/doc/Makefile.in .
cp $bdir/WebServer/libhttpserver-master/src/Makefile.in .
cp $bdir/WebServer/libhttpserver-master/test/Makefile.in .
cp $bdir/WebServer/libhttpserver-master/examples/Makefile.in .

/bin/bash $bdir/WebServer/libhttpserver-master/bootstrap

/bin/bash $bdir/WebServer/libhttpserver-master/configure
make -j4
make install
rm -rf /tmp/microhttpd.build