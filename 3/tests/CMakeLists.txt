cmake_minimum_required(VERSION 3.5)
# 'Google_test' is the subproject name
project(Google_tests)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
# 'lib' is the folder with Google Test sources
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run test.cpp ../Prowler.cpp ../Characteristics.h ../Enemy.cpp ../Enemy_info.cpp ../Item.cpp ../HUD.cpp ../Tile.cpp)
target_link_libraries(Google_Tests_run sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(Google_Tests_run gtest gtest_main)