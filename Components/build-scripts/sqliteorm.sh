#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/sqliteorm.build ]; then
	mkdir /tmp/sqliteorm.build
fi
cd /tmp/sqliteorm.build
cmake $bdir/sqlite_orm-master
make -j4 
make install

rm -rf /tmp/sqliteorm.build