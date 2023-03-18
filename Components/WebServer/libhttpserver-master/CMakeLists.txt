cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "httpserver")
project($PROJECT_NAME VERSION 0.9.75)

set(ENV{CPPFLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/../libmicrohttpd-0.9.75/src/include)
message("CPPFLAGS $ENV{CPPFLAGS}")
set(ENV{LDFLAGS} -L${CMAKE_BINARY_DIR}/lib)
message("LDFLAGS $ENV{LDFLAGS}")

#if(NOT EXISTS ${CMAKE_BINARY_DIR}/libmicrohttpd.pc)
message("Bootstrapping httpserver...")
execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})

message("Configuring httpserver...")
execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/configure" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})

#endif()
add_compile_definitions(HAVE_CONFIG_H=1)
add_compile_definitions(USE_FASTOPEN=1)
add_compile_definitions(HTTPSERVER_COMPILATION)

SET(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)
message("SRC_DIR=${SRC_DIR}")

add_library(httpserver SHARED 
    ${SRC_DIR}basic_auth_fail_response.cpp
    ${SRC_DIR}deferred_response.cpp
    ${SRC_DIR}digest_auth_fail_response.cpp
    ${SRC_DIR}file_info.cpp
    ${SRC_DIR}file_response.cpp
    ${SRC_DIR}http_request.cpp
    ${SRC_DIR}http_resource.cpp
    ${SRC_DIR}http_response.cpp
    ${SRC_DIR}http_utils.cpp
    ${SRC_DIR}string_response.cpp
    ${SRC_DIR}string_utilities.cpp
    ${SRC_DIR}webserver.cpp
)
target_include_directories(httpserver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
