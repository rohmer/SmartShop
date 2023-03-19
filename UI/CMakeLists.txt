cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "UI")
project($PROJECT_NAME VERSION 1.0.0)

add_library(UI SHARED
	LogTable.cpp
	MainWindow.cpp
	NodeWidgetManager.cpp
	WindowManager.cpp
	Images/noWifi.c
	Images/Wifi1.c
	Images/Wifi2.c
	Images/Wifi3.c
	Images/Wifi4.c
)
target_include_directories(UI PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/LVGL/lv_port_linux_frame_buffer/lvgl
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/oatpp-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/cJSON-master
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite3
	${CMAKE_CURRENT_SOURCE_DIR}/../NetworkTools
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/libwpa/wpa_cli_oper
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/libwpa/wpa_supplicant-2.6/wpa_supplicant
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/LVGL/lv_port_linux_frame_buffer/lv_drivers
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/LVGL/lv_port_linux_frame_buffer
)

target_link_libraries(UI DB)
target_link_libraries(UI sqlite3)
target_link_libraries(UI RaspUtils)
target_link_libraries(UI cjson)
target_link_libraries(UI NetworkTools)
target_link_libraries(UI Logger)
target_link_libraries(UI lvgl)
target_link_libraries(UI lv_drivers)
target_link_libraries(UI NodeWidget)
target_link_libraries(UI UIWidget)

add_subdirectory(NodeWidget NodeWidget)
add_subdirectory(StatusWidget StatusWidget)
add_subdirectory(UIWidget UIWidget)

add_compile_definitions(LV_COLOR_DEPTH=16)
add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
add_compile_definitions(LV_CONF_H)

add_dependencies(NodeWidget UIWidget)
add_dependencies(StatusWidget UI)
add_dependencies(StatusWidget UIWidget)