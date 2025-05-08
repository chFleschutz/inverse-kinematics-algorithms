cmake_minimum_required(VERSION 3.12)

project(ik-algorithms)

option(BUILD_DEMOS "Build the demo projects" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glm)

add_library(ik-algorithms STATIC 
	"src/CCD.h"
	"src/FABRIK.h"
	"src/IKSolver.h"
	"src/Skeleton.h"
	"src/Skeleton.cpp"
	
	
)

target_link_libraries(ik-algorithms PUBLIC
	glm
)

target_include_directories(ik-algorithms PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

if(BUILD_DEMOS)
	add_subdirectory(demos/ik_console_demo)
	add_subdirectory(demos/ik_gui_demo)
endif()
