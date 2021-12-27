cmake_minimum_required(VERSION 3.20)
project(LongNum_menu)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(LongNum_menu main.cpp menu.cpp menu.h)

include(FindPkgConfig)
find_package(LongNum REQUIRED)
include_directories(${LONGNUM_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${LONGNUM_LIBRARY})