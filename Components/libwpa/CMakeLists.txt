cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "libwpa")
project($PROJECT_NAME VERSION 2.6)

add_compile_definitions(CONFIG_CTRL_IFACE)
add_compile_definitions(CONFIG_CTRL_IFACE_UNIX)

add_library(libwpa SHARED
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_cli_oper/bitarray.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_supplicant-2.6/src/common/cli.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_supplicant-2.6/src/utils/common.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_cli_oper/compat.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_supplicant-2.6/src/utils/edit.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_supplicant-2.6/src/utils/eloop.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_supplicant-2.6/wpa_supplicant/libwpa_cli_wrapper.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_supplicant-2.6/src/utils/os_unix.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_cli_oper/smartlist.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_cli_oper/wpa_cli_oper.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_supplicant-2.6/src/common/wpa_ctrl.c
	${CMAKE_CURRENT_SOURCE_DIR}/wpa_supplicant-2.6/src/utils/wpa_debug.c
)
target_include_directories(libpa PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/wpa_supplicant-2.6/src/utils)