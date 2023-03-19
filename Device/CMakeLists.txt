cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "Device")
project($PROJECT_NAME VERSION 1.0.0)


add_library(Device SHARED 
	DeviceBase.cpp
	DeviceConfig.cpp
	DeviceManager.cpp
	GPIODevice.cpp
	I2CDevice.cpp
)

target_include_directories(Device PUBLIC
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

target_link_libraries(Device DB)
target_link_libraries(Device sqlite3)
target_link_libraries(Device RaspUtils)
target_link_libraries(Device cjson)
target_link_libraries(Device cpp-base64)
target_link_libraries(Device Logger)
target_link_libraries(Device md5)
target_link_libraries(Device pigpio)
target_link_libraries(Device SensorEvent)

add_subdirectory(AHTX0Sensor AHTX0Sensor)
add_subdirectory(MCP9808Sensor MCP9808Sensor)
add_subdirectory(PCA9685Device PCA9685Device)
add_subdirectory(PM25AQISensor PM25AQISensor)
add_subdirectory(SwitchDevice SwitchDevice)
add_subdirectory(TelemetryAgent TelemetryAgent)