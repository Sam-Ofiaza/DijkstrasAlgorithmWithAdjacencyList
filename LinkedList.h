//
// Created by Sam on 11/26/2021.
//

#ifndef DIJKSTRA_SALGORITHMWITHADJACENCYLIST_LINKEDLIST_H
#define DIJKSTRA_SALGORITHMWITHADJACENCYLIST_LINKEDLIST_H

#include <iostream>

class Vertex;

class LinkedList {
public:
    LinkedList();

    Vertex * getHead();
    Vertex * getTail();
    Vertex * get(std::string name);

    void add(Vertex * v);
    void removeFirst();

    bool contains(std::string name);

    void printList();

private:
    Vertex * head;
    Vertex * tail;
};


#endif //DIJKSTRA_SALGORITHMWITHADJACENCYLIST_LINKEDLIST_H
