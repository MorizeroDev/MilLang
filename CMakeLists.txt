cmake_minimum_required(VERSION 3.26)
project(GetMacOSXLocale)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-framework Foundation")

add_library(GetMacOSXLocale SHARED lib.cpp lib.h)

add_library(GetMacOSXLocaleStatic lib.cpp lib.h)
add_executable(GetMacOSXLocaleMain lib.h main.cpp)
target_link_libraries(GetMacOSXLocaleMain GetMacOSXLocaleStatic)
