cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "NodeAuth")
project($PROJECT_NAME VERSION 1.0.0)


add_library(NodeAuth SHARED 
	NodeAuth.cpp
)

target_include_directories(NodeAuth PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../DB
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/WebServer/cpr-master/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/oatpp-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/cJSON-master	
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite3
)

target_link_libraries(NodeAuth DB)
target_link_libraries(NodeAuth sqlite3)
target_link_libraries(NodeAuth microhttpd)
target_link_libraries(NodeAuth httpserver)
