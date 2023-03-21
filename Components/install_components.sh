#!/bin/bash

/bin/bash build-scripts/lvgl.sh
cp -R Scheduler-master/*.h /usr/local/include
/bin/bash build-scripts/nettle.sh
/bin/bash build-scripts/microhttpd.sh
/bin/bash build-scripts/httpserver.sh
/bin/bash build-scripts/bzip.sh
/bin/bash build-scripts/cjson.sh
/bin/bash build-scripts/base64.sh
/bin/bash build-scripts/date.sh
/bin/bash build-scripts/archive.sh
/bin/bash build-scripts/uuid.sh

#libwpa
if [ ! -d /tmp/wpa.build ]; then
	mkdir /tmp/wpa.build
fi
cd /tmp/wpa.build

