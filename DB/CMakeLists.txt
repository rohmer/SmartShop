cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "DB")
project($PROJECT_NAME VERSION 1.0.0)


add_library(DB SHARED 
	DB.cpp
)

target_include_directories(DB PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite_orm-master/include/sqlite_orm/
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite3/
)

message("IncludeDirs: ${CMAKE_CURRENT_SOURCE_DIR}../Components/sqlite_orm-master/include/sqlite_orm/ \n${CMAKE_CURRENT_SOURCE_DIR}../Components/sqlite3/")

target_link_libraries(DB PRIVATE sqlite3)