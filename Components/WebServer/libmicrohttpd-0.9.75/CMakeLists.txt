cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "microhttpd")
project($PROJECT_NAME VERSION 0.9.75)

set(ENV{CPPFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/../libmicrohttpd-0.9.75/src/include)
message("CPPFLAGS $ENV{CPPFLAGS}")
set(ENV{LDFLAGS} -L${CMAKE_BINARY_DIR}/lib)
message("LDFLAGS $ENV{LDFLAGS}")

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/configure)
message("Bootstrapping microhttpd...")
file(CHMOD ${CMAKE_CURRENT_SOURCE_DIR}/bootstrap} PERMISSIONS WORLD_EXECUTE WORLD_READ)
execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})
endif()

file(CHMOD ${CMAKE_CURRENT_SOURCE_DIR}/configure PERMISSIONS WORLD_EXECUTE WORLD_READ)
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build)
message("Configuring microhttpd...")
message("Creating dir: ${CMAKE_CURRENT_SOURCE_DIR}/build")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
message("Executing ${CMAKE_CURRENT_SOURCE_DIR}/configure in ${CMAKE_CURRENT_SOURCE_DIR}/build")
execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/configure" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
)
message("RESULT: " ${result})
message("OUTPUT: " ${output})
endif()

add_compile_definitions(HAVE_CONFIG_H=1)
add_compile_definitions(BUILD_MHD_LIB=1)

SET(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)
message("SRC_DIR=${SRC_DIR}")

file(GLOB_RECURSE src1 
    "src/lib/*.c"
    "src/lib/*.h"
)
    
add_library(microhttpd SHARED 
    ${src1}
)
target_include_directories(microhttpd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(microhttpd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../libmicrohttpd-0.9.75/src/include)
