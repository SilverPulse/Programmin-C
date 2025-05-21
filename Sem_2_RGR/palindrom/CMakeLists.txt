
cmake_minimum_required(VERSION 3.10)
project(palindrom C)

set(CMAKE_C_STANDARD 11)

add_executable(palindrom
    src/main.c
    src/preprocess.c
    src/manacher.c
    src/utils.c)

enable_testing()
add_subdirectory(tests)
