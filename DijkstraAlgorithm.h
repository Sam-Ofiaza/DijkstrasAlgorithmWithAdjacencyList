//
// Created by Sam on 11/26/2021.
//

// Extremely inefficient due to implementation of adjacency list as nested linked lists from project description

#ifndef DIJKSTRA_SALGORITHMWITHADJACENCYLIST_DIJKSTRAALGORITHM_H
#define DIJKSTRA_SALGORITHMWITHADJACENCYLIST_DIJKSTRAALGORITHM_H

#include "Vertex.h"
#include "LinkedList.h"
#include "Stack.h"
#include <unordered_map>
#include <climits>
#include <vector>
#include <stack>

enum dataType {cost, time};

struct flightPlan {
    std::string from, to;
    dataType type;
};

class DijkstraAlgorithm {
public:
    DijkstraAlgorithm(LinkedList list);

    void runAlgorithm(Vertex * v, dataType type);
    void printBestPath(std::string destination, dataType type);
    void printIterativeBacktracking(std::string destination, dataType type);

    bool contains(std::vector<std::string> v, std::string s);

private:
    LinkedList adjacencyList;
    std::unordered_map<Vertex *, int> leastPathData;
    std::unordered_map<Vertex *, Vertex *> predecessors;
    std::vector<std::pair<Vertex *, int>> unrelaxedEdges;

    Vertex * source;
};


#endif //DIJKSTRA_SALGORITHMWITHADJACENCYLIST_DIJKSTRAALGORITHM_H
