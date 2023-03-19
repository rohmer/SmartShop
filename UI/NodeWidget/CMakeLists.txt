cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "NodeWidget")
project($PROJECT_NAME VERSION 1.0.0)


file(GLOB_RECURSE NodeWidget_SRC CONFIGURE_DEPENDS "*.h" "*.cpp" "*.c")

add_compile_definitions(LV_COLOR_DEPTH=16)
add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
add_compile_definitions(LV_CONF_H)

add_library(NodeWidget SHARED ${NodeWidget_SRC})
target_include_directories(NodeWidget PUBLIC
target_include_directories(UIWidget PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/LVGL/lv_port_linux_frame_buffer/lvgl
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/oatpp-master/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/spdlog-1.x/include
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/sqlite_orm-master/include/sqlite_orm
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/cJSON-master
	${CMAKE_CURRENT_SOURCE_DIR}/../../Components/sqlite3
)
)

target_link_libraries(NodeWidget DB)
target_link_libraries(NodeWidget sqlite3)
target_link_libraries(NodeWidget RaspUtils)
target_link_libraries(NodeWidget cjson)
target_link_libraries(NodeWidget NetworkTools)
target_link_libraries(NodeWidget Logger)
target_link_libraries(NodeWidget lvgl)
target_link_libraries(NodeWidget lv_drivers)
