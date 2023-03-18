cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "httpserver")
project($PROJECT_NAME VERSION 0.9.75)

set(ENV{CPPFLAGS} ${CMAKE_CURRENT_SOURCE_DIR}/../libmicrohttpd-0.9.75/src/include)
message("CPPFLAGS $ENV{CPPFLAGS}")

#if(NOT EXISTS ${CMAKE_BINARY_DIR}/libmicrohttpd.pc)
message("Bootstrapping httpserver...")
exec_program("bash ${CMAKE_CURRENT_SOURCE_DIR}/bootstrap" ${CMAKE_CURRENT_SOURCE_DIR}
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})

message("Configuring httpserver...")
exec_program("bash ${CMAKE_CURRENT_SOURCE_DIR}/configure" ${CMAKE_CURRENT_SOURCE_DIR}
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})

#endif()

