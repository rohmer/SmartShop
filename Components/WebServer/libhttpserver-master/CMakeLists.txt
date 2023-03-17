cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "httpserver")
project($PROJECT_NAME VERSION 0.9.75)

if(NOT EXISTS ${CMAKE_BINARY_DIR}/libmicrohttpd.pc)
message("Configuring httpserver...")
exec_program("bash ${CMAKE_BINARY_DIR}/bootstrap" 
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})
endif()

set(env{CPPFLAGS} ${CMAKE_CURRENT_SOURCE_DIR}/../libmicrohttpd-0.9.75/src/include)
message("CPPFLAGS $env{CPPFLAGS}")