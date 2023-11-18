cmake_minimum_required(VERSION 3.26)
project(Milang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework Foundation")

add_library(Milang SHARED lib.cpp lib.h)

add_library(MilangStatic lib.cpp lib.h)

add_executable(MilangMain lib.h main.cpp)
target_link_libraries(MilangMain MilangStatic)
