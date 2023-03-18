cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "Logger")
project($PROJECT_NAME VERSION 1.0.0)


add_library(Logger SHARED 
	Logger.cpp	
)

target_include_directories(Logger PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../DB
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/WebServer/cpr-master/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/oatpp-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/cJSON-master	
)