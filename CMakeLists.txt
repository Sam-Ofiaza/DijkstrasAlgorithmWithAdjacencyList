cmake_minimum_required(VERSION 3.17)
project(Dijkstra_sAlgorithmWithAdjacencyList)

set(CMAKE_CXX_STANDARD 14)

add_executable(Dijkstra_sAlgorithmWithAdjacencyList main.cpp Vertex.cpp Vertex.h LinkedList.cpp LinkedList.h DijkstraAlgorithm.cpp DijkstraAlgorithm.h Stack.cpp Stack.h)