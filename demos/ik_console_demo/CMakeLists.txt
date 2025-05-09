cmake_minimum_required(VERSION 3.12)

project(ik-console-demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ik-console-demo "main.cpp")
target_link_libraries(ik-console-demo PRIVATE ik-algorithms)
