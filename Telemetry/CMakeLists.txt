cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "Telemetry")
project($PROJECT_NAME VERSION 1.0.0)


add_library(Telemetry SHARED 
	Telemetry.cpp
)

target_include_directories(Telemetry PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite_orm-master/include/sqlite_orm/
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite3/
	${CMAKE_CURRENT_SOURCE_DIR}/../Logger
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/oatpp-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/cJSON-master
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../DB
)

target_link_libraries(Telemetry DB)
target_link_libraries(Telemetry sqlite3)
target_link_libraries(Telemetry Logger)
target_link_libraries(Telemetry oatpp)
target_link_libraries(Telemetry cjson)
