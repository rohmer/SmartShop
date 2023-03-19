cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "NetworkTools")
project($PROJECT_NAME VERSION 1.0.0)


file(GLOB NT_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_library(NetworkTools ${NT_SRC})
target_include_directories(NetworkTools PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/libwpa/wpa_cli_oper
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/libwpa/wpa_supplicant-2.6/wpa_supplicant
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../DB
)

target_link_libraries(NetworkTools DB)
target_link_libraries(NetworkTools sqlite3)
target_link_libraries(NetworkTools wpa)
