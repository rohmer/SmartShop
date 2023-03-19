cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "EndpointClient")
project($PROJECT_NAME VERSION 1.0.0)


add_library(EndpointClient SHARED 
	EndpointClient.cpp
)

target_include_directories(EndpointClient PUBLIC
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
)

target_link_libraries(RESTServer DB)
target_link_libraries(RESTServer sqlite3)
target_link_libraries(RESTServer RaspUtils)
target_link_libraries(RESTServer cjson)
target_link_libraries(RESTServer SensorEvent)
target_link_libraries(RESTServer oatpp)