cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "gnutls")
project($PROJECT_NAME VERSION 3.6.16)

message("Configuring...")
exec_program("bash ${CMAKE_CURRENT_SOURCE_DIR}/configure" 
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})

file(GLOB gnutlssrc
    
)