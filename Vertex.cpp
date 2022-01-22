//
// Created by Sam on 11/26/2021.
//

#include "Vertex.h"
#include "LinkedList.h"

Vertex::Vertex(std::string name)
    : name(name), next(nullptr), list(nullptr) {}

Vertex::Vertex(std::string name, int cost, int time)
    : name(name), cost(cost), time(time), next(nullptr), list(nullptr) {}

std::string Vertex::getName() {
    return name;
}

int Vertex::getCost() {
    return cost;
}

int Vertex::getTime() {
    return time;
}

Vertex *Vertex::getNext() {
    return next;
}

LinkedList *Vertex::getList() {
    return list;
}

void Vertex::setNext(Vertex *next) {
    this->next = next;
}

void Vertex::setList(LinkedList *list) {
    this->list = list;
}
