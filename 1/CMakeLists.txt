cmake_minimum_required(VERSION 3.20)
project(LongNum_static_overload)

set(CMAKE_CXX_STANDARD 20)

add_library(LongNum_static_overload LongNum_static_overload.cpp)
add_executable(test tmp.cpp LongNum_static_overload.cpp)