cmake_minimum_required(VERSION 3.8)
project(LinkedList)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c GADT.c)
add_executable(LinkedList ${SOURCE_FILES} GADT.c)