cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "microhttpd")
project($PROJECT_NAME VERSION 0.9.75)

message("Configuring libmicrohttpd...")
exec_program("bash ${CMAKE_CURRENT_SOURCE_DIR}/configure" 
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})

add_compile_definitions(HAVE_CONFIG_H=1)
add_compile_definitions(BUILD_MHD_LIB=1)
add_
SET(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/)
file(GLOB libmicrohttpdsrc
    ${SRC_DIR}action_continue.c                  
)
target_include_directories(microhttpd PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_library(microhttpd ${libmicrohttpdsrc})
