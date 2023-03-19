cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "SensorEvent")
project($PROJECT_NAME VERSION 1.0.0)


add_library(SensorEvent SHARED 
	BinaryData.cpp
	ColorData.cpp
	FloatData.cpp
	IntData.cpp
	SensorEvent.cpp
	StringData.cpp
	SwitchData.cpp
	VectorData.cpp
)

target_include_directories(SensorEvent PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../DB
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/WebServer/cpr-master/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/oatpp-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/cJSON-master	
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite3
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/cpp-base64-master
	${CMAKE_CURRENT_SOURCE_DIR}/../Logger
)

target_link_libraries(SensorEvent DB)
target_link_libraries(SensorEvent sqlite3)
target_link_libraries(SensorEvent oatpp)
target_link_libraries(SensorEvent Logger)
target_link_libraries(SensorEvent cjson)
target_link_libraries(SensorEvent cpp-base64)
