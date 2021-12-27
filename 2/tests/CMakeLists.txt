cmake_minimum_required(VERSION 3.20)
project(LongNum_tests)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
add_executable(LongNum_tests main.cpp test.cpp)
include(FindPkgConfig)
find_package(LongNum REQUIRED)
include_directories(${LONGNUM_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${LONGNUM_LIBRARY})
target_link_libraries(${PROJECT_NAME} gtest gtest_main)


