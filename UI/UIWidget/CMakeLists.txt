cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "UIWidget")
project($PROJECT_NAME VERSION 1.0.0)


file(GLOB UIWidget_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
target_compile_features(UIWidget PUBLIC cxx_std_17)

add_library(UIWidget ${UIWidget_SRC})
target_include_directories(UIWidget PUBLIC
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

target_link_libraries(UIWidget DB)
target_link_libraries(UIWidget sqlite3)
target_link_libraries(UIWidget RaspUtils)
target_link_libraries(UIWidget cjson)
target_link_libraries(UIWidget NetworkTools)
target_link_libraries(UIWidget Logger)
target_link_libraries(UIWidget lvgl)
target_link_libraries(UIWidget lv_drivers)
