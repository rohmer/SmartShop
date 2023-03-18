cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "bz2")
project($PROJECT_NAME VERSION 1.0.8)

add_compile_options(
    -fpic -fPIC -Wall -Winline -O2 -g)

add_compile_definitions(_FILE_OFFSET_BITS=64)
add_library(bz2 SHARED
	blocksort.c
	huffman.c    
    crctable.c   
    randtable.c  
    compress.c   
    decompress.c 
    bzlib.c
)