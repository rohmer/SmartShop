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
)
