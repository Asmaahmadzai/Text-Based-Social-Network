cmake_minimum_required(VERSION 4.2)
project(A03sysc2006 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(A03sysc2006
        a3_functions.c
        a3_functions.h
        a3_nodes.h
        main.c)
