cmake_minimum_required(VERSION 3.19)
SET(PROJECT_NAME "sqlite3")
project($PROJECT_NAME VERSION 0.9.75)

message("Configuring sqlite3...")
message("CURRENT_SORUCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
file(CHMOD_RECURSE ${CMAKE_CURRENT_SOURCE_DIR} PERMISSIONS WORLD_EXECUTE WORLD_READ)

execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/configure" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})

