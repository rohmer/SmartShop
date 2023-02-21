cmake_minimum_required(VERSION 3.12)
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(PicoClient C CXX ASM)
include(PicoSDKConfig.cmake)
pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
add_executable(unique_board_id
        unique_board_id.c
        )

target_link_libraries(unique_board_id
        pico_stdlib
        pico_unique_id
        )

# create map/bin/hex file etc.
pico_add_extra_outputs(unique_board_id)

# add url via pico_set_program_url
# example_auto_set_url(unique_board_id)
