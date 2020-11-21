cmake_minimum_required(VERSION 3.13)
project(Lab2-Life)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/fmt)
include_directories(lib/fmt/include)

add_subdirectory(lib/google_tests)
include_directories(lib/google_test/include)
include_directories(lib/google_mock/include)

file(GLOB SOURCES src/*.cpp src/*.h tests/*.cpp tests/*.h)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} fmt)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
target_link_libraries(${PROJECT_NAME} gmock gmock_main)