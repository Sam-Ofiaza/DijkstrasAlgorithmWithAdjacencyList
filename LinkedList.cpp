//
// Created by Sam on 11/26/2021.
//

#include "LinkedList.h"
#include "Vertex.h"

LinkedList::LinkedList()
    : head(nullptr), tail(nullptr) {}

Vertex *LinkedList::getHead() {
    return head;
}

Vertex *LinkedList::getTail() {
    return tail;
}

Vertex *LinkedList::get(std::string name) {
    Vertex * current = head;
    while(current != nullptr) {
        if(current->getName() == name) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

void LinkedList::add(Vertex *v) {
    if(head == nullptr) {
        head = v;
        tail = v;
    }
    else {
        tail->setNext(v);
        tail = v;
    }
}

void LinkedList::removeFirst() {
    if(head != nullptr) {
        head = head->getNext();
    }
}

bool LinkedList::contains(std::string name) {
    if(head == nullptr) {
        return false;
    }
    Vertex * current = head;
    while(current != nullptr) {
        if(current->getName() == name) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

void LinkedList::printList() {
    Vertex * current = head;
    while(current != nullptr) {
        if(current->getList() != nullptr && current->getList()->getHead() != nullptr) {
            std::cout << current->getName() << " -> ";
            current->getList()->printList();
            std::cout << std::endl;
        }
        else {
            std::cout << current->getName() << " ";
        }
        current = current->getNext();
    }
}
