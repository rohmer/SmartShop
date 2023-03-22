#!/bin/bash

bdir=$(pwd)
if [ ! -d /tmp/zeroconf.build ]; then
	mkdir /tmp/zeroconf.build
fi
cd /tmp/zeroconf.build
cmake $bdir/ZeroConf
