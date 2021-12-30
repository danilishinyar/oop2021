cmake_minimum_required(VERSION 3.20)
project(LongNum_static)

set(CMAKE_CXX_STANDARD 20)

add_library(LongNum_static LongNum_static.cpp)
add_executable(test tmp.cpp LongNum_static.cpp)