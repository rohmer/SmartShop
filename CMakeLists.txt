set(PROJECT_NAME "SmartShop")
set(PROJECT_VERSION VERSION 1.0.0)
project(SmartShop)

option(BUILD_DEBUG "Builds debug release" ON)
option(BUILD_RELEASE "Builds release" OFF)
if(BUILD_DEBUG)
	set(CMAKE_BUILD_TYPE "Debug")
	message("Building Debug")
endif()
if(BUILD_RELEASE)
	set(CMAKE_BUILD_TYPE "Release")
	message("Building Release")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# CppUTest
include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG        master # or use release tag, eg. v4.0
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

add_subdirectory(Server Server)