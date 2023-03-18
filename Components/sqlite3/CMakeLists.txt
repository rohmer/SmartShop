cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "microhttpd")
project($PROJECT_NAME VERSION 0.9.75)

message("Configuring libmicrohttpd...")
message("CURRENT_SORUCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
file(CHMOD ${CMAKE_CURRENT_SOURCE_DIR/configure} PERMISSIONS WORLD_EXECUTE)
execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/configure" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})

