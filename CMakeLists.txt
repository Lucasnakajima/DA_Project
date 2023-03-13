cmake_minimum_required(VERSION 3.23)
project(Projeto)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto main.cpp Station.cpp Station.h Graph.cpp Graph.h basic_graph_classes/GraphBasic.cpp basic_graph_classes/GraphBasic.h basic_graph_classes/VertexEdge.cpp basic_graph_classes/VertexEdge.h Connection.cpp Connection.h)
