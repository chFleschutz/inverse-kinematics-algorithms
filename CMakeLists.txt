cmake_minimum_required(VERSION 3.12)

project(IKSolverProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(ik-algorithms STATIC ${HEADERS} ${SOURCES})


# Optional Example Project
option(BUILD_EXAMPLE "Build the example project" ON)

if(BUILD_EXAMPLE)
	message(STATUS "Building example project")
	add_subdirectory(example)
endif()
