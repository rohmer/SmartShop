cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "RESTServer")
project($PROJECT_NAME VERSION 1.0.0)


add_library(RESTServer SHARED 
	RESTServer.cpp
)

target_include_directories(RESTServer PUBLIC
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
)

target_link_libraries(RESTServer DB)
target_link_libraries(RESTServer sqlite3)
target_link_libraries(RESTServer microhttpd)
target_link_libraries(RESTServer httpserver)
target_link_libraries(RESTServer RaspUtils)
