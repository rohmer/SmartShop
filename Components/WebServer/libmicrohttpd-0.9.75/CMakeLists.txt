cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "microhttpd")
project($PROJECT_NAME VERSION 0.9.75)

message("Configuring libmicrohttpd...")
message("CURRENT_SORUCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build})
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/MHD_config.h)
execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/configure" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
)
message("RESULT: " ${result})
message("OUTPUT: " ${output})
endif()
endif()

add_compile_definitions(HAVE_CONFIG_H=1)
add_compile_definitions(BUILD_MHD_LIB=1)
file(GLOB libmicrohttpdsrc
     "*.h"
     "*.cpp"
)
add_library(microhttpd SHARED ${libmicrohttpdsrc})
target_include_directories(microhttpd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(microhttpd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/build)
target_include_directories(microhttpd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
