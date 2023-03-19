cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "LogEndpoint")
project($PROJECT_NAME VERSION 1.0.0)


add_library(LogEndpoint SHARED 
	LogEndpoint.cpp	
)

target_include_directories(LogEndpoint PUBLIC
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
	${CMAKE_CURRENT_SOURCE_DIR}/../Device
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/date-master/include/date
)

target_link_libraries(LogEndpoint DB)
target_link_libraries(LogEndpoint sqlite3)
target_link_libraries(LogEndpoint RaspUtils)
target_link_libraries(LogEndpoint cjson)
target_link_libraries(LogEndpoint oatpp)
target_link_libraries(LogEndpoint NodeAuth)
