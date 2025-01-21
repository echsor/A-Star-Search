cmake_minimum_required(VERSION 3.28.3)
project(A_star)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-error=unused-variable -g -fsanitize=address -fno-omit-frame-pointer -O0")

add_executable(A_star main.cpp
        AStar.cpp
        AStar.h
        ReadGraph.cpp
        ReadGraph.h
        ReadHeuristic.cpp
        ReadHeuristic.h)
