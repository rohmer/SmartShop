cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "libmicrohttpd")
project($PROJECT_NAME VERSION 0.9.75)

message("Configuring...")
exec_program("bash ${CMAKE_CURRENT_SOURCE_DIR}/configure" 
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})