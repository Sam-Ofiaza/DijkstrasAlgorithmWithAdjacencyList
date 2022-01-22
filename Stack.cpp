//
// Created by Sam on 11/27/2021.
//

#include "Stack.h"

Stack::Stack() {

}

void Stack::push(pathWithState *v) {
    list.push_back(v);
}

void Stack::pop() {
    list.pop_back();
}

pathWithState *Stack::peek() {
    return list.back();
}

// Checks if a path has a vertex
bool Stack::pathContainsName(std::vector<Vertex *> p, Vertex *v) {
    for(int i = 0; i < p.size(); i++) {
        if(p.at(i)->getName() == v->getName()) {
            return true;
        }
    }
    return false;
}


bool Stack::empty() {
    return list.empty();
}

void Stack::printPath(std::vector<Vertex *> p) {
    for(int i = 0; i < p.size(); i++) {
        if(i == p.size()-1) {
            std::cout << p.at(i)->getName();
        }
        else {
            std::cout << p.at(i)->getName() << " -> ";
        }
    }
}

void Stack::printStack() {
    for(int i = 0; i < list.size(); i++) {
        for(int j = 0; j < list[i]->path.size(); j++) {
            if(j == list[i]->path.size()-1) {
                std::cout << list[i]->path[j]->getName();
            }
            else {
                std::cout << list[i]->path[j]->getName() << " -> ";
            }
        }
        std::cout << ", Cost: " << list[i]->cost << ", Time: " << list[i]->time << ".\n";
    }
}