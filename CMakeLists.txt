cmake_minimum_required(VERSION 3.26)
project(Milang)

set(CMAKE_CXX_STANDARD 17)

set(MILANG_SRC src/lib.h)
set(MILANG_CXX_FLAGX)

if (DEFINED MILANG_BUILD_APPLE AND MILANG_BUILD_APPLE STREQUAL ON)
    set(MILANG_CXX_FLAGX "-framework Foundation")
    set(MILANG_SRC ${MILANG_SRC} src/lib_apple.cpp)
elseif (DEFINED MILANG_BUILD_WINDOWS AND MILANG_BUILD_WINDOWS STREQUAL ON)
    set(MILANG_SRC ${MILANG_SRC} src/lib_windows.cpp)
else()
    message(FATAL_ERROR "????????")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MILANG_CXX_FLAGX}")

add_library(Milang SHARED ${MILANG_SRC})
add_library(MilangStatic ${MILANG_SRC})

add_executable(MilangMain src/lib.h src/main.cpp)
target_link_libraries(MilangMain MilangStatic)
