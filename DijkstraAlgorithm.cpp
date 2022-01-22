//
// Created by Sam on 11/26/2021.
//

#include "DijkstraAlgorithm.h"

DijkstraAlgorithm::DijkstraAlgorithm(LinkedList list)
    : adjacencyList(list), source(nullptr) {}

void DijkstraAlgorithm::runAlgorithm(Vertex *v, dataType type) {
    source = v;

    // Initialize/reset leastPathData, predecessors, and unrelaxedEdges
    Vertex * current = adjacencyList.getHead();
    leastPathData.clear();
    predecessors.clear();
    unrelaxedEdges.clear();
    while(current != nullptr) {
        if(current == source) {
            std::pair<Vertex *, int> p(current, 0);
            unrelaxedEdges.push_back(p);
        }
        else {
            std::pair<Vertex *, int> p(current, INT_MAX);
            unrelaxedEdges.push_back(p);
        }
        current = current->getNext();
    }
    for(std::pair<Vertex *, int> p : unrelaxedEdges) {
        leastPathData.insert(p);
        std::pair<Vertex *, Vertex *> p2(p.first, nullptr);
        predecessors.insert(p2);
    }

    // Algorithm
    while(!unrelaxedEdges.empty()) {
        // Debugging: confirm unrelaxedEdges is being modified
        /*for(int i = 0; i < unrelaxedEdges.size(); i++) {
            std::cout << "unrelaxedEdges.at(" << i << ") = <" << unrelaxedEdges.at(i).first->getName() << ", " << unrelaxedEdges.at(i).second << ">.\n";
        }*/

        std::pair<Vertex *, int> currentLeastUnknownVertex(nullptr, INT_MAX);

        // Find least edge from unrelaxedEdges, save it to currentLeastUnknownVertex, and delete it from the vector
        int eraseIndex = 0;
        for(int i = 0; i < unrelaxedEdges.size(); i++) {
            if(unrelaxedEdges.at(i).second < currentLeastUnknownVertex.second) {
                currentLeastUnknownVertex = unrelaxedEdges.at(i);
                eraseIndex = i;
            }
        }
        unrelaxedEdges.erase(unrelaxedEdges.begin()+eraseIndex);

        // Before checking currentLeastUnknownVertex's adjacent vertices, confirm a least pair was actually found
        if(currentLeastUnknownVertex.first != nullptr){
            // Loop through adjacent vertices
            Vertex * currentAdjacentVertex = currentLeastUnknownVertex.first->getList()->getHead(); // Current adjacent vertex of currentLeastUnknownVertex
            Vertex * currentAdjacentVertexForMaps; // leastPathData stores vertices with linked lists that are different from vertices in the linked lists themselves
            while(currentAdjacentVertex != nullptr) {
                currentAdjacentVertexForMaps = adjacencyList.get(currentAdjacentVertex->getName());

                // New references for readability
                int storedQuantity = leastPathData.at(currentAdjacentVertexForMaps);
                int possibleLowerQuantity;
                switch(type) {
                    case cost: possibleLowerQuantity = leastPathData.at(currentLeastUnknownVertex.first) + currentAdjacentVertex->getCost(); break;
                    case time: possibleLowerQuantity = leastPathData.at(currentLeastUnknownVertex.first) + currentAdjacentVertex->getTime(); break;
                }

                // Reconsider new edge weight of current adjacent vertex
                if(possibleLowerQuantity < storedQuantity) {
                    leastPathData.at(currentAdjacentVertexForMaps) = possibleLowerQuantity;
                    predecessors.at(currentAdjacentVertexForMaps) = currentLeastUnknownVertex.first;

                    // Find and update edge in unrelaxedEdges
                    for(int i = 0; i < unrelaxedEdges.size(); i++) {
                        if(unrelaxedEdges.at(i).first == currentAdjacentVertexForMaps) {
                            unrelaxedEdges.at(i).second = possibleLowerQuantity;
                            i = unrelaxedEdges.size(); // End loop after target found
                        }
                    }
                }
                currentAdjacentVertex = currentAdjacentVertex->getNext();
            }
        }
    }

    // Debugging: confirm maps are correct
    /*std::cout << "\nleastPathData:\n";
    for(std::pair<Vertex *, int> p : leastPathData) {
        std::cout << "<" << p.first->getName() << ", " << p.second << ">\n";
    }
    std::cout << "\nPath:\n";
    for(std::pair<Vertex *, Vertex *> p : predecessors) {
        if(p.second == nullptr) {
            std::cout << "<" << p.first->getName() << ", >\n";
        }
        else {
            std::cout << "<" << p.first->getName() << ", " << p.second->getName() << ">\n";
        }
    }*/
}

void DijkstraAlgorithm::printBestPath(std::string destination, dataType type) {
    std::vector<std::pair<std::string, int>> path;

    Vertex * current = adjacencyList.get(destination);
    while(current != source) {
        std::pair<std::string, int> p;
        p.first = current->getName();
        switch(type) {
            case cost:  p.second = current->getList()->get(predecessors.at(current)->getName())->getTime(); break;
            case time: p.second = current->getList()->get(predecessors.at(current)->getName())->getCost(); break;
        }
        path.push_back(p);
        current = predecessors.at(current);
    }
    path.push_back(std::pair<std::string, int>(current->getName(), 0));

    int otherData = 0;
    std::cout << "Best path: ";
    for(int i = path.size()-1; i >= 0; i--) {
        if(i == 0) {
            std::cout << path[i].first << ". ";
        }
        else {
            std::cout << path[i].first << " -> ";
        }
        otherData += path[i].second;
    }
    switch(type) {
        case cost: std::cout << "Time: " << otherData << " Cost: " << leastPathData.at(adjacencyList.get(destination)); break;
        case time: std::cout << "Time: " << leastPathData.at(adjacencyList.get(destination)) << " Cost: " << otherData; break;
    }
    std::cout << std::endl;
}

void DijkstraAlgorithm::printIterativeBacktracking(std::string destination, dataType type) {
    std::vector<pathWithState *> allCalls; // Stores all calls for deletion
    std::vector<pathWithState *> paths; // Stores all paths from source to destination along with their costs and times
    pathWithState * p;

    // Go through source's adjacent vertices and store every path that leads to destination
    // Skip cycles by skipping vertices that lead to source
    std::vector<Vertex *> currentPath; // To be stored in a pathWithState in a Stack when a new unprocessed vertex is found
    currentPath.push_back(source);

    Vertex * currentVertex = source->getList()->getHead();
    Stack unprocessedCalls; // Stores each unprocessed path with its current cost and time, emulates recursive call stack
    // Initialize unprocessedCalls with source's adjacent vertices
    while(currentVertex != nullptr) {
        currentPath.push_back(currentVertex);
        p = new pathWithState(currentPath, currentVertex->getCost(), currentVertex->getTime());
        allCalls.push_back(p);
        unprocessedCalls.push(p);
        currentVertex = currentVertex->getNext();
        currentPath.pop_back();
    }

    // Evaluate all unprocessed calls, storing all paths from source to destination with their costs and times
    // and searching for any remaining unprocessed vertices
    pathWithState * currentCall;
    while(!unprocessedCalls.empty()) {
        currentCall = unprocessedCalls.peek();
        unprocessedCalls.pop();
        currentPath = currentCall->path;

        // Go through current's adjacent vertices, store every path leading to destination.
        // Also, look for any more unknown vertices while avoiding cycles and dead ends.
        // If found, add them to unprocessedVertices and add their costs and times to the current pathWithState (call)
        currentVertex = adjacencyList.get(currentPath.back()->getName());

        //std::cout << "currentVertex in outer loop = " << currentVertex->getName() << "\n";

        if(currentVertex->getName() == destination) {
            p = new pathWithState(currentPath, currentCall->cost, currentCall->time);
            allCalls.push_back(p);
            paths.push_back(p);

            //std::cout << "Adding call from outer loop, ending vertex = " << currentVertex->getName() << ", cost = " << p->cost << ", time = " << p->time << ".\n";
        }
        else if(currentVertex->getList() != nullptr) { // Check if dead end or only adjacent vertex is destination
            currentVertex = currentVertex->getList()->getHead();

            while(currentVertex != nullptr) {

                //std::cout << "currentVertex in inner loop = " << currentVertex->getName() << "\n";

                if(currentVertex->getName() == destination) {
                    currentPath.push_back(currentVertex);
                    p = new pathWithState(currentPath, currentCall->cost + currentVertex->getCost(),currentCall->time + currentVertex->getTime());
                    allCalls.push_back(p);
                    paths.push_back(p);
                    currentPath.pop_back();

                    //std::cout << "Found destination in inner loop, cost = " << p->cost << ", time = " << p->time << ".\n";
                }
                else if(!unprocessedCalls.pathContainsName(currentPath, currentVertex)) { // Avoid duplicate calls and cycles
                    currentPath.push_back(currentVertex);
                    p = new pathWithState(currentPath, currentCall->cost + currentVertex->getCost(),currentCall->time + currentVertex->getTime());
                    allCalls.push_back(p);
                    unprocessedCalls.push(p);
                    currentPath.pop_back();

                    //std::cout << "Adding call from inner loop, ending vertex = " << currentVertex->getName() << ", cost = " << p->cost << ", time = " << p->time << ".\n";
                }
                currentVertex = currentVertex->getNext();
            }
        }
    }

    // Find the best three paths and print
    int leastQuantity = INT_MAX;
    int otherQuantity = INT_MAX;
    int eraseIndex;
    for(int i = 0; i < 3; i++) {
        if(paths.size() > 0) {
            for (int j = 0; j < paths.size(); j++) {
                if (type == time && paths[j]->time < leastQuantity) {
                    leastQuantity = paths[j]->time;
                    otherQuantity = paths[j]->cost;
                    eraseIndex = j;
                } else if (type == cost && paths[j]->cost < leastQuantity) {
                    leastQuantity = paths[j]->cost;
                    otherQuantity = paths[j]->time;
                    eraseIndex = j;
                }
            }
            std::cout << "Path " << i + 1 << ": ";
            for (int j = 0; j < paths[eraseIndex]->path.size(); j++) {
                if (j == paths[eraseIndex]->path.size() - 1) {
                    std::cout << paths[eraseIndex]->path[j]->getName() << ". ";
                } else {
                    std::cout << paths[eraseIndex]->path[j]->getName() << " -> ";
                }
            }
            switch (type) {
                case cost:
                    std::cout << "Time: " << otherQuantity << " Cost: " << leastQuantity << "\n";
                    break;
                case time:
                    std::cout << "Time: " << leastQuantity << " Cost: " << otherQuantity << "\n";
                    break;
            }

            paths.erase(paths.begin() + eraseIndex);
            leastQuantity = INT_MAX;
            otherQuantity = INT_MAX;
            eraseIndex = 0;
        }
    }

    // allCalls cleanup
    for(int i = 0; i < allCalls.size(); i++) {
        delete allCalls[i];
    }
}

bool DijkstraAlgorithm::contains(std::vector<std::string>v , std::string s) {
    for(int i = 0; i < v.size(); i++) {
        if(v[i] == s) {
            return true;
        }
    }
    return false;
}