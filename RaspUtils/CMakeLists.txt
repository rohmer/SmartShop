cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "RaspUtils")
project($PROJECT_NAME VERSION 1.0.0)


add_library(RaspUtils SHARED 
	CPUInfo.cpp
	JSON.cpp
)

target_include_directories(RaspUtils PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/cJSON-master
)
target_link_libraries(RaspUtil cjson)