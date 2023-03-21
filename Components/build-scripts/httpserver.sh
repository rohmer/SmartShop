#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/httpserver.build ]; then
	mkdir /tmp/httpserver.build 
fi
cd /tmp/httpserver.build
cp $bdir/WebServer/libhttpserver-master/* .
cp -R $bdir/WebServer/libhttpserver-master/m4 .
cp -R $bdir/WebServer/libhttpserver-master/*.am .
cp -r $bdir/WebServer/libhttpserver-master/libhttpserver.pc.in .
cp -r $bdir/WebServer/libhttpserver-master/doc/Makefile.in ./doc
cp -r $bdir/WebServer/libhttpserver-master/src/Makefile.in ./src
cp -r $bdir/WebServer/libhttpserver-master/test/Makefile.in ./test
cp -r $bdir/WebServer/libhttpserver-master/examples/Makefile.in ./examples

/bin/bash $bdir/WebServer/libhttpserver-master/bootstrap

/bin/bash $bdir/WebServer/libhttpserver-master/configure
make -j4
make install
rm -rf /tmp/microhttpd.build