cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "AHTX0Sensor")
project($PROJECT_NAME VERSION 1.0.0)


add_library(AHTX0Sensor SHARED 
	AHTX0Sensor.cpp
)

target_include_directories(AHTX0Sensor PUBLIC
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
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/date-master/include/
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/pigpio-master
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/Scheduler-master	
)

target_link_libraries(AHTX0Sensor DB)
target_link_libraries(AHTX0Sensor sqlite3)
target_link_libraries(AHTX0Sensor RaspUtils)
target_link_libraries(AHTX0Sensor cjson)
target_link_libraries(AHTX0Sensor cpp-base64)
target_link_libraries(AHTX0Sensor Logger)
target_link_libraries(AHTX0Sensor md5)
target_link_libraries(AHTX0Sensor pigpio)
target_link_libraries(AHTX0Sensor SensorEvent)