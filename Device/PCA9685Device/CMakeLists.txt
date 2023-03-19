cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "PCA9685Device")
project($PROJECT_NAME VERSION 1.0.0)


add_library(PCA9685Device SHARED 
	PCA9685Device.cpp
)

target_include_directories(PCA9685Device PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../../DB
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/WebServer/cpr-master/include
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/oatpp-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/cJSON-master	
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/sqlite3
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/WebServer/libhttpserver-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/WebServer/libmicrohttpd-0.9.75/src/include
	${CMAKE_CURRENT_SOURCE_DIR}/../../RaspUtils
	${CMAKE_CURRENT_SOURCE_DIR}/../../SensorEvent	
	${CMAKE_CURRENT_SOURCE_DIR}/../../Logger
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/cpp-base64-master
	${CMAKE_CURRENT_SOURCE_DIR}/..
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/date-master/include/
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/pigpio-master
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/Scheduler-master	
)

target_link_libraries(PCA9685Device DB)
target_link_libraries(PCA9685Device sqlite3)
target_link_libraries(PCA9685Device RaspUtils)
target_link_libraries(PCA9685Device cjson)
target_link_libraries(PCA9685Device cpp-base64)
target_link_libraries(PCA9685Device Logger)
target_link_libraries(PCA9685Device md5)
target_link_libraries(PCA9685Device pigpio)
target_link_libraries(PCA9685Device SensorEvent)