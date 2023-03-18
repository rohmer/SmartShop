cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "RaspUtils")
project($PROJECT_NAME VERSION 1.0.0)


add_library(RapsUtils SHARED 
	CPUInfo.cpp
	JSON.cpp
)
