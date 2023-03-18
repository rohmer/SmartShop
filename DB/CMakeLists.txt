cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "DB")
project($PROJECT_NAME VERSION 1.0.0)

add_library(DB SHARED 
	DB.cpp
)

include_directories(
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}../Components/sqlite_orm-master/include/sqlite_orm
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}../Components/cJSON-master
)

target_link_libraries(DB PUBLIC sqlite3)