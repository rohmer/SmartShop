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
/bin/bash build-scripts/wpa.sh
/bin/bash build-scripts/md5.sh
/bin/bash build-scripts/oatpp.sh
/bin/bash build-scripts/pigpio.sh
/bin/bash build-scripts/sigar.sh
cp -R spdlog-1.x/include/* /usr/local/include
/bin/bash build-scripts/sqlite3.sh
/bin/bash build-scripts/sqliteorm.sh
/bin/bash build-scripts/cxxopts.sh
/bin/bash build-scripts/wiringx.sh
/bin/bash build-scripts/zeroconf.sh