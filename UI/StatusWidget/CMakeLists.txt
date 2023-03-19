cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "StatusWidget")
project($PROJECT_NAME VERSION 1.0.0)


file(GLOB StatusWidget_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_compile_definitions(LV_COLOR_DEPTH=16)
add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
add_compile_definitions(LV_CONF_H)

add_library(StatusWidget ${StatusWidget_SRC})
target_include_directories(StatusWidget PUBLIC
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

target_link_libraries(StatusWidget DB)
target_link_libraries(StatusWidget sqlite3)
target_link_libraries(StatusWidget RaspUtils)
target_link_libraries(StatusWidget cjson)
target_link_libraries(StatusWidget NetworkTools)
target_link_libraries(StatusWidget Logger)
target_link_libraries(StatusWidget lvgl)
target_link_libraries(StatusWidget lv_drivers)
target_link_libraries(StatusWidget UI)
target_link_libraries(StatusWidget UIWidget)
