cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "EventEndpoint")
project($PROJECT_NAME VERSION 1.0.0)


add_library(EventEndpoint SHARED 
	EventEndpoint.cpp
)

target_include_directories(EventEndpoint PUBLIC
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
	${CMAKE_CURRENT_SOURCE_DIR}/../SensorEvent
	${CMAKE_CURRENT_SOURCE_DIR}/../Logger
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/cpp-base64-master

)

target_link_libraries(EndpointClient DB)
target_link_libraries(EndpointClient sqlite3)
target_link_libraries(EndpointClient microhttpd)
target_link_libraries(EndpointClient httpserver)
target_link_libraries(EndpointClient RaspUtils)
target_link_libraries(EndpointClient cjson)
target_link_libraries(EndpointClient NodeAuth)
target_link_libraries(EndpointClient SensorEvent)

add_subdirectory(EndpointClient EndpointClient)