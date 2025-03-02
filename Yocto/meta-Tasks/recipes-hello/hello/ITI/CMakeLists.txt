
cmake_minimum_required(VERSION 3.2)
project(hello C)

if(DEFINED ENV{CC})
    set(CMAKE_C_COMPILER $ENV{CC})
endif()

add_executable(${PROJECT_NAME} main.c)


