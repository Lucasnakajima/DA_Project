cmake_minimum_required(VERSION 3.23)
project(Projeto)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto main.cpp station.cpp station.h operations.cpp operations.h Graph.cpp Graph.h VertexEdge.cpp VertexEdge.h)
