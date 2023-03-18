cmake_minimum_required(VERSION 3.19)
SET(PROJECT_NAME "uuid")
project($PROJECT_NAME VERSION 1.0)

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/config.h)
    file(CHMOD ${CMAKE_CURRENT_SOURCE_DIR/configure} PERMISSIONS WORLD_EXECUTE)
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/configure" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE result
               OUTPUT_VARIABLE output
               )
    message("RESULT: " ${result})
    message("OUTPUT: " ${output})
endif()
add_library(uuid SHARED 
 clear.c
 compare.c
 copy.c
 gen_uuid.c
 isnull.c
 pack.c
 parse.c
 randutils.c
 unpack.c
 unparse.c
 uuid_time.c
)