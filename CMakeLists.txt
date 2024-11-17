cmake_minimum_required(VERSION 3.12)

project(ik-algorithms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
	"src/CCD.h"
	"src/FABRIK.h"
	"src/IKSolver.h"
	"src/Skeleton.h"
	"src/Skeleton.cpp"
	"src/Vector2.h"
	"src/Vector2.cpp"
)

add_library(ik-algorithms STATIC ${SRC})
include_directories(${PROJECT_SOURCE_DIR}/src)

# Optional Example Project
option(BUILD_EXAMPLE "Build the example project" ON)

if(BUILD_EXAMPLE)
	message(STATUS "Building example project")
	add_subdirectory(example)
endif()
