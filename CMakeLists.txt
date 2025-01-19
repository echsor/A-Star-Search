cmake_minimum_required(VERSION 3.30)
project(A_star)

set(CMAKE_CXX_STANDARD 23)

add_executable(A_star main.cpp
        Node.cpp
        Node.h
        AStar.cpp
        AStar.h
        ReadGraph.cpp
        ReadGraph.h
        ReadHeuristic.cpp
        ReadHeuristic.h)
