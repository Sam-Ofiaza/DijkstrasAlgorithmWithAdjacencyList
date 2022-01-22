//
// Created by Sam on 11/27/2021.
//

// Stores each unprocessed path with its current cost and time, emulates recursive call stack

#ifndef DIJKSTRA_SALGORITHMWITHADJACENCYLIST_STACK_H
#define DIJKSTRA_SALGORITHMWITHADJACENCYLIST_STACK_H

#include <vector>
#include "Vertex.h"
#include <iostream>

struct pathWithState {
    pathWithState(std::vector<Vertex *> path, int cost, int time)
        : path(path), cost(cost), time(time) {}

    std::vector<Vertex *> path;
    int cost, time;
};

class Stack {
public:
    Stack();

    void push(pathWithState * v);
    void pop();
    pathWithState * peek();

    bool pathContainsName(std::vector<Vertex *> p, Vertex * v);
    bool empty();

    void printPath(std::vector<Vertex *> p);
    void printStack();

private:
    std::vector<pathWithState *> list;
};


#endif //DIJKSTRA_SALGORITHMWITHADJACENCYLIST_STACK_H
