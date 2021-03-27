cmake_minimum_required(VERSION 3.10)
project(jderobot_cpp_challenge)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/labyrinth.cpp")
add_executable(labyrinth ${SOURCES})