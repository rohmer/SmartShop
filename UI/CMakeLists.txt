cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "UI")
project($PROJECT_NAME VERSION 1.0.0)


file(GLOB UI_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_library(UI ${UI_SRC})
target_include_directories(UI PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/LVGL/lv_port_linux_frame_buffer/lvgl
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/LVGL/lv_port_linux_frame_buffer/lv_drivers
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../DB
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/rapidjson-master/include/rapidjson/msinttypes
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/LVGL/lv_port_linux_frame_buffer/lvgl
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/libwpa/wpa_cli_oper
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/libwpa/wpa_supplicant-2.6/wpa_supplicant
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/oatpp-master/src

target_link_libraries(TelemetryAgent DB)
target_link_libraries(TelemetryAgent sqlite3)
target_link_libraries(TelemetryAgent RaspUtils)
target_link_libraries(TelemetryAgent cjson)
target_link_libraries(TelemetryAgent cpp-base64)
target_link_libraries(TelemetryAgent Logger)
target_link_libraries(TelemetryAgent md5)
target_link_libraries(TelemetryAgent pigpio)
target_link_libraries(TelemetryAgent SensorEvent)
target_link_libraries(TelemetryAgent Telemetry)