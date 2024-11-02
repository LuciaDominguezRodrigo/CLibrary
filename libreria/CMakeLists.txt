cmake_minimum_required(VERSION 3.29)
project(libreria C)

set(CMAKE_C_STANDARD 23)

add_library(libreria STATIC libreria.c
        test.c)
