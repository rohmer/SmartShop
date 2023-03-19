cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "NodeWidget")
project($PROJECT_NAME VERSION 1.0.0)


file(GLOB NodeWidget_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_library(NodeWidget ${NodeWidget_SRC})
target_include_directories(NodeWidget PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/LVGL/lv_port_linux_frame_buffer/lvgl
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/LVGL/lv_port_linux_frame_buffer/lv_drivers
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../../DB
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/rapidjson-master/include/rapidjson/msinttypes
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/LVGL/lv_port_linux_frame_buffer/lvgl
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/libwpa/wpa_cli_oper
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/libwpa/wpa_supplicant-2.6/wpa_supplicant
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/oatpp-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(NodeWidget DB)
target_link_libraries(NodeWidget sqlite3)
target_link_libraries(NodeWidget RaspUtils)
target_link_libraries(NodeWidget cjson)
target_link_libraries(NodeWidget NetworkTools)
target_link_libraries(NodeWidget Logger)
target_link_libraries(NodeWidget lvgl)
target_link_libraries(NodeWidget lv_drivers)