#!/bin/bash

/bin/bash build-scripts/lvgl.sh
#Scheduler
cp -R Scheduler-master/*.h /usr/local/include


#WebServer
#Nettle
if [ ! -d /tmp/nettle.build ]; then
	mkdir /tmp/nettle.build
fi
cd /tmp/nettle.build
#/bin/bash $bdir/WebServer/nettle-3.8/configure --disable-documentation
make -j4 
make install
#rm -rf /tmp/nettle.build

#Microhttpd
apt install libgnutls28-dev libguntls30 -y
if [ ! -d /tmp/microhttpd.build ]; then
	mkdir /tmp/microhttpd.build
fi
cd /tmp/microhttpd.build
#/bin/bash $bdir/WebServer/libmicrohttpd-0.9.75/configure --disable-doc
make -j4
make install
#rm -rf /tmp/microhttpd.build

if [ ! -d /tmp/httpserver.build ]; then
	mkdir /tmp/httpserver.build 
fi
cd /tmp/httpserver.build
cp $bdir/WebServer/libhttpserver-master/configure.ac /tmp/httpserver.build
cp -R $bdir/WebServer/libhttpserver-master/m4 .
cp -R $bdir/WebServer/libhttpserver-master/*.am .

#/bin/bash $bdir/WebServer/libhttpserver-master/bootstrap

#/bin/bash $bdir/WebServer/libhttpserver-master/configure
make -j4
make install
#rm -rf /tmp/microhttpd.build

#bzip2
if [ ! -d /tmp/bzip2.build ]; then
	mkdir /tmp/bzip2.build
fi
cd /tmp/bzip2.build
cp -R $bdir/bzip2-1.0.8/* .
make -j4 -f Makefile-libbz2_so
make install

#rm -rf /tmp/bzip2.build

#cJSON
if [ ! -d /tmp/cjson.build ]; then
	mkdir /tmp/cjson.build
fi
cd /tmp/cjson.build
cp -R $bdir/cJSON-master .
make -j4 
make install

#rm -rf /tmp/cjson.build

#cpp-base64
if [ ! -d /tmp/base64.build ]; then
	mkdir /tmp/base64.build 
fi
cd /tmp/base64.build
cmake $bdir/cpp-base64-master
make
cp libcpp-base64.so /usr/local/lib

#rm -rf /tmp/base64.build

#date
if [ ! -d /tmp/date.build ]; then
	mkdir /tmp/date.build
fi
cd /tmp/date.build
cmake $bdir/date-master
make install

# rm -rf /tmp/date.build

#libarchive
if [ ! -d /tmp/archive.build ]; then
	mkdir /tmp/archive.build
fi
cd /tmp/archive.build
cmake $bdir/libarchive-3.6.2
make -j4
make install

#rm -rf /tmp/archive.build

#libuuid
if [ ! -d /tmp/uuid.build ]; then
	mkdir /tmp/uuid.build
fi
cd /tmp/uuid.build
cp -R $bdir/libuuid-master/* .
bash ./configure
make -j4
make install

#rm -rf /tmp/uuid.build

#libwpa
if [ ! -d /tmp/wpa.build ]; then
	mkdir /tmp/wpa.build
fi
cd /tmp/wpa.build

