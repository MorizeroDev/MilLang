cmake_minimum_required(VERSION 3.26)
project(GetMacOSXLocale)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-framework Foundation")

add_library(MilLang SHARED lib.cpp lib.h)

add_library(MilLangStatic lib.cpp lib.h)
add_executable(MilLangMain lib.h main.cpp)
target_link_libraries(MilLangMain MilLangStatic)
