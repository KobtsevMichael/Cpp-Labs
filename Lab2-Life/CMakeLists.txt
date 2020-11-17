cmake_minimum_required(VERSION 3.13)
project(Lab2-Life)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_subdirectory(lib/fmt)
include_directories(lib/fmt/include)

file(GLOB SOURCES src/*.cpp src/*.h)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} fmt)