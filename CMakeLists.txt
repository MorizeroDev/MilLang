cmake_minimum_required(VERSION 3.26)
project(Milang)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_SHARED_LIBS "Build shared library" ON)


# ---------------------------------------------------------------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# Windows DLLs are "runtime" for CMake. Output them to "bin" like the Visual Studio projects do.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Reset output dirs for multi-config builds
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
endforeach(OUTPUTCONFIG)


if(BUILD_SHARED_LIBS)
    set(MILANG_LIBRARY_PREFIX "${CMAKE_SHARED_LIBRARY_PREFIX}")
else()
    set(MILANG_LIBRARY_PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# ---------------------------------------------------------------------------------------


set(MILANG_SRC)
set(MILANG_CXX_FLAGX)

if (APPLE)
    set(MILANG_CXX_FLAGX "-framework Foundation")
    set(MILANG_SRC ${MILANG_SRC} src/lib_apple.cpp)
elseif (WIN32)
    set(MILANG_SRC ${MILANG_SRC} src/lib_windows.cpp)
else()
    message(FATAL_ERROR "The platform is not supported.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MILANG_CXX_FLAGX}")

add_library(Milang ${MILANG_SRC})
target_include_directories(Milang
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add compile definitions. MILIZE_DLL is visible to all targets in the project such as MilangMainApp.
if(BUILD_SHARED_LIBS)
    target_compile_definitions(Milang PUBLIC MILIZE_DLL PRIVATE MILIZE_BUILDING_SHARED_LIBS)
endif()


# ---------------------------------------------------------------------------------------
add_subdirectory(app)
