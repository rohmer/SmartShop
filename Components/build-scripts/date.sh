#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/date.build ]; then
	mkdir /tmp/date.build
fi
cd /tmp/date.build
cmake $bdir/date-master
make install

rm -rf /tmp/date.build