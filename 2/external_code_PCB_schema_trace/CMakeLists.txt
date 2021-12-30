cmake_minimum_required(VERSION 3.20)
project(lib_D)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lib_D
        Menu.cpp
        Menu.h
        PCB.cpp
        PCB.h tmp.cpp lee.cpp)
