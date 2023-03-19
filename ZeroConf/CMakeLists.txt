cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "ZeroConf")
project($PROJECT_NAME VERSION 1.0.0)


file(GLOB ZeroConf_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_library(ZeroConf SHARED ${ZeroConf_SRC})
target_include_directories(ZeroConf PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/LVGL/lv_port_linux_frame_buffer/lvgl
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/oatpp-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/cJSON-master
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/sqlite3
)

target_link_libraries(ZeroConf DB)
target_link_libraries(ZeroConf sqlite3)
target_link_libraries(ZeroConf RaspUtils)
target_link_libraries(ZeroConf cjson)
target_link_libraries(ZeroConf Logger)
