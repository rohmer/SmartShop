cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "uuid")
project($PROJECT_NAME VERSION 1.0)

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