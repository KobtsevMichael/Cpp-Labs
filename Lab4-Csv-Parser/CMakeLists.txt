cmake_minimum_required(VERSION 3.5)
project(Lab4-Csv-Parser)
set(CMAKE_CXX_STANDARD 17)

file(
    GLOB SOURCES
    src/*.cpp src/*.h
    src/**/*.cpp src/**/*.h
)
add_executable(Lab4-Csv-Parser ${SOURCES})
