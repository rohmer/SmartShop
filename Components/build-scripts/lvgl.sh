#!/bin/bash
#LVGL
bdir=$(pwd)
printf "$bdir\n"
if [ ! -d /tmp/lvgl.build ]; then
	mkdir  /tmp/lvgl.build
fi
cd /tmp/lvgl.build
cmake $bdir/LVGL/lv_port_linux_frame_buffer -DLV_LVGL_H_INCLUDE_SIMPLE=ON -DBUILD_SHARED_LIBS=ON
make -j4
make install
cd $bdir
rm -rf /tmp/lvgl.build