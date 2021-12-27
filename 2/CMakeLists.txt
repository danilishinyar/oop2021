cmake_minimum_required(VERSION 3.20)
project(LongNum)

set(CMAKE_CXX_STANDARD 20)

add_library(LongNum LongNum.cpp)
add_executable(test tmp.cpp LongNum.cpp)