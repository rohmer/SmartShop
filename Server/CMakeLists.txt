cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "Server")
project($PROJECT_NAME VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build the components
add_compile_definitions(LV_COLOR_DEPTH=16)
add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
add_compile_definitions(LV_CONF_H)
add_subdirectory(../Components Components)
add_subdirectory(../DB DB)
add_subdirectory(../RaspUtils RaspUtils)
add_subdirectory(../Logger Logger)
add_subdirectory(../SensorEvent SensorEvent)
add_subdirectory(../Telemetry Telemetry)
add_subdirectory(../NodeAuth NodeAuth)
add_subdirectory(../RESTServer RESTServer)
add_subdirectory(../EventEndpoint EventEndpoint)
add_subdirectory(../DeviceRegistration DeviceRegistration)
add_subdirectory(../LogEndpoint LogEndpoint)
add_subdirectory(../Device Device)
add_subdirectory(../NetworkTools NetworkTools)
add_subdirectory(../UI UI)
add_subdirectory(../ZeroConf ZeroConf)

file(GLOB Server_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_executable(Server ${Server_SRC})

target_include_directories(Server PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../DB
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/WebServer/cpr-master/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/oatpp-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/cJSON-master	
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite3
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/WebServer/libhttpserver-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/WebServer/libmicrohttpd-0.9.75/src/include
	${CMAKE_CURRENT_SOURCE_DIR}/../RaspUtils
	${CMAKE_CURRENT_SOURCE_DIR}/../Logger
	${CMAKE_CURRENT_SOURCE_DIR}/../EventEndpoint
	${CMAKE_CURRENT_SOURCE_DIR}/../LogEndpoint
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/date-master/include/date
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/LVGL/lv_port_linux_frame_buffer/lv_drivers
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/LVGL/lv_port_linux_frame_buffer
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/LVGL/lv_port_linux_frame_buffer/lvgl
	${CMAKE_CURRENT_SOURCE_DIR}/../NetworkTools
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/libwpa/wpa_cli_oper
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/libwpa/wpa_supplicant-2.6/wpa_supplicant
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/Scheduler-master
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/cpp-base64-master
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/pigpio-master
	${CMAKE_CURRENT_SOURCE_DIR}/../Device
)

target_link_libraries(Server DB)
target_link_libraries(Server sqlite3)
target_link_libraries(Server RaspUtils)
target_link_libraries(Server cjson)
target_link_libraries(Server NetworkTools)
target_link_libraries(Server Logger)
target_link_libraries(Server lvgl)
target_link_libraries(Server lv_drivers)
target_link_libraries(Server NodeWidget)
target_link_libraries(Server cpp-base64)
target_link_libraries(Server uuid)
target_link_libraries(Server wpa)
target_link_libraries(Server md5)
target_link_libraries(Server oatpp)
target_link_libraries(Server sigar)
target_link_libraries(Server sqlite3)
target_link_libraries(Server httpserver)
target_link_libraries(Server microhttpd)
target_link_libraries(Server Device)
target_link_libraries(Server DeviceRegistration)
target_link_libraries(Server EndpointClient)
target_link_libraries(Server EventEndpoint)
target_link_libraries(Server LogEndpoint)
target_link_libraries(Server NetworkTools)
target_link_libraries(Server NodeAuth)
target_link_libraries(Server UI)
target_link_libraries(Server UIWidget)
target_link_libraries(Server ZeroConf)
target_link_libraries(Server SensorEvent)
target_link_libraries(Server RESTServer)
target_link_libraries(Server RaspUtils)
target_link_libraries(Server Logger)
target_link_libraries(dl)
target_link_libraries(pthread)
target_link_libraries(gnutls)
target_link_libraries(gmp)
target_link_libraries(nettle)
target_link_libraries(unistring)
target_link_libraries(hogweed)
target_link_libraries(TASN1)
target_link_libraries(p11-kit)
target_link_libraries(idn2)
target_link_libraries(ffi)
target_link_libraries(atomic)