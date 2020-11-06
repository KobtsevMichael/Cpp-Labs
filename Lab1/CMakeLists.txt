cmake_minimum_required(VERSION 3.13)
project(Lab1)
set(CMAKE_CXX_STANDARD 14)

#Add the google test subdirectory
add_subdirectory(Google_tests)

#include googletest/include dir
include_directories(Google_tests/googletest/include)

#include the googlemock/include dir
include_directories(Google_tests/googlemock/include)

set(SOURCE_FILES rna.cpp tests.cpp)
add_executable(Lab1 ${SOURCE_FILES})

#Link with GoogleTest
target_link_libraries(Lab1 gtest gtest_main)

#Link with GoogleMock
target_link_libraries(Lab1 gmock gmock_main)
