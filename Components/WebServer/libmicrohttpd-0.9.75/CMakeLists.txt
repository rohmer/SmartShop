cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "microhttpd")
project($PROJECT_NAME VERSION 0.9.75)

message("Configuring libmicrohttpd...")
message("CURRENT_SORUCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build})
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/MHD_config.h)
execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/configure" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
)
message("RESULT: " ${result})
message("OUTPUT: " ${output})
endif()
endif()

add_compile_definitions(HAVE_CONFIG_H=1)
add_compile_definitions(BUILD_MHD_LIB=1)
SET(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/)
file(GLOB libmicrohttpdsrc
    ${SRC_DIR}action_continue.c        
    ${SRC_DIR}action_from_response.c
    ${SRC_DIR}action_parse_post.c
    ${SRC_DIR}action_process_upload.c
    ${SRC_DIR}action_suspend.c
    ${SRC_DIR}connection_add.c
    ${SRC_DIR}connection_call_handlers.c
    ${SRC_DIR}connection_cleanup.c
    ${SRC_DIR}connection_close.c
    ${SRC_DIR}connection_finish_forward.c
    ${SRC_DIR}connection_info.c
    ${SRC_DIR}connection_options.c
    ${SRC_DIR}connection_update_last_activity.c
    ${SRC_DIR}daemon_close_all_connections.c
    ${SRC_DIR}daemon_create.c
    ${SRC_DIR}daemon_destroy.c
    ${SRC_DIR}daemon_epoll.c
    ${SRC_DIR}daemon_get_timeout.c
    ${SRC_DIR}daemon_info.c
    ${SRC_DIR}daemon_ip_limit.c
    ${SRC_DIR}daemon_options.c
    ${SRC_DIR}daemon_poll.c
    ${SRC_DIR}daemon_quiesce.c
    ${SRC_DIR}daemon_run.c
    ${SRC_DIR}daemon_select.c
    ${SRC_DIR}daemon_start.c
    ${SRC_DIR}init.c
    ${SRC_DIR}internal.c
    ${SRC_DIR}memorypool.c
    ${SRC_DIR}mhd_compat.c
    ${SRC_DIR}mhd_itc.c
    ${SRC_DIR}mhd_mono_clock.c
    ${SRC_DIR}mhd_sockets.c
    ${SRC_DIR}mhd_str.c
    ${SRC_DIR}mhd_threads.c
    ${SRC_DIR}panic.c
    ${SRC_DIR}reason_phrase.c
    ${SRC_DIR}request.c
    ${SRC_DIR}request_info.c
    ${SRC_DIR}request_resume.c
    ${SRC_DIR}response.c
    ${SRC_DIR}response_for_upgrade.c
    ${SRC_DIR}response_from_buffer.c
    ${SRC_DIR}response_from_callback.c
    ${SRC_DIR}response_from_fd.c
    ${SRC_DIR}response_options.c
    ${SRC_DIR}sysfdsetsize.c
    ${SRC_DIR}tsearch.c
    ${SRC_DIR}upgrade_process.c
    ${SRC_DIR}version.c
)
add_library(microhttpd SHARED ${libmicrohttpdsrc})
target_include_directories(microhttpd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(microhttpd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/build)
target_include_directories(microhttpd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
