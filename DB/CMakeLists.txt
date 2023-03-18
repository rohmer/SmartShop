cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "DB")
project($PROJECT_NAME VERSION 1.0.0)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(header_dir_list)

list(LENGTH header_dir_list header_dir_list_count)
message(STATUS "[INFO] Found ${header_dir_list_count} header directories.")

add_library(DB SHARED 
	DB.cpp
)

include_directories(
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}../Components/sqlite_orm-master/include/sqlite_orm
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}../Components/cJSON-master
)

target_link_libraries(DB PUBLIC sqlite3)