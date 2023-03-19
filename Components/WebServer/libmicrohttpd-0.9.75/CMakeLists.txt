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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/connection.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/connection.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/reason_phrase.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/daemon.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/internal.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/internal.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/memorypool.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/memorypool.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_mono_clock.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_mono_clock.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_limits.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/sysfdsetsize.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/sysfdsetsize.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_str.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_str.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_send.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_send.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_assert.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_sockets.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_sockets.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_itc.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_itc.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_itc_types.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_compat.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_compat.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/response.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/response.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_threads.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_threads.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_locks.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/tsearch.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/tsearch.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/postprocessor.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/digestauth.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_bithelpers.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_byteorder.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/mhd_align.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/md5.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/md5.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/sha256.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/sha256.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/basicauth.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/base64.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/base64.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/connection_https.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microhttpd/connection_https.h
)

target_include_directories(microhttpd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(microhttpd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
target_include_directories(microhttpd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/build)
