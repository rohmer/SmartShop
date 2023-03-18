cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "DB")
project($PROJECT_NAME VERSION 1.0.0)

target_include_directories(DB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}../Components/sqlite_orm-master/include/sqlite_orm)

add_library(DB SHARED 
	DB.cpp
)