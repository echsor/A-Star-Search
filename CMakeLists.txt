cmake_minimum_required(VERSION 3.30)
project(A_star)

set(CMAKE_CXX_STANDARD 20)

add_executable(A_star main.cpp
        Node.cpp
        Node.h
        AStar.cpp
        AStar.h
        ReadGraph.cpp
        ReadGraph.h)
