cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "TelemetryAgent")
project($PROJECT_NAME VERSION 1.0.0)


add_library(TelemetryAgent SHARED 
	TelemetryAgent.cpp
)

target_include_directories(TelemetryAgent PUBLIC
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
	${CMAKE_CURRENT_SOURCE_DIR}/../../Telemetry
)

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