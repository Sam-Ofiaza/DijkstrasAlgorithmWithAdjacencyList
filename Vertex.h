//
// Created by Sam on 11/26/2021.
//

#ifndef DIJKSTRA_SALGORITHMWITHADJACENCYLIST_VERTEX_H
#define DIJKSTRA_SALGORITHMWITHADJACENCYLIST_VERTEX_H

#include <string>

class LinkedList;

class Vertex {

public:
    Vertex(std::string name);
    Vertex(std::string name, int cost, int time);

    std::string getName();
    int getCost();
    int getTime();
    Vertex * getNext();
    LinkedList * getList();

    void setNext(Vertex * next);
    void setList(LinkedList * list);

private:
    std::string name;
    int cost, time;
    Vertex * next;
    LinkedList * list;
};


#endif //DIJKSTRA_SALGORITHMWITHADJACENCYLIST_VERTEX_H
