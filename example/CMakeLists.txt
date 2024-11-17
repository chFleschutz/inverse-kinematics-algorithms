cmake_minimum_required(VERSION 3.12)

project(ik-algorithms-example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ik-algorithms-example "main.cpp")
target_link_libraries(ik-algorithms-example PRIVATE ik-algorithms)
