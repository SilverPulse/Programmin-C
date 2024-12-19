cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# set project name
project(list-c
    LANGUAGES C
    VERSION 0.0.0
)

# set release mode as default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

#
include_directories(".")


#
add_executable( list-c
	main.c
	list_files.c
	list_files.h
)

#	
enable_testing()

add_test(
    NAME
        "test_list-c"
    COMMAND
        $<TARGET_FILE:list-c> 
        /
    WORKING_DIRECTORY
        ${CMAKE_HOME_DIRECTORY}
)
