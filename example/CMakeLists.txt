cmake_minimum_required(VERSION 3.12)

project(IKExampleProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(IKExample main.cpp)

target_link_libraries(IKExample PRIVATE IKSolver)
