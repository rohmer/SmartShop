cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "cpp-base64")
project($PROJECT_NAME VERSION 1.0)

add_library(cpp-base64 SHARED base64.cpp)
