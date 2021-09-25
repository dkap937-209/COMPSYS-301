cmake_minimum_required(VERSION 3.20)
project(Astar)

set(CMAKE_CXX_STANDARD 14)

add_executable(Astar
        A_Star.cpp A_star_header.h helperFunctions.cpp)
