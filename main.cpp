#include "DijkstraAlgorithm.h"
#include <fstream>
#include <sstream>

bool processFlightData(LinkedList &list, std::vector<Vertex *> &vertices, std::vector<Vertex *> &adjacentVertices, std::vector<LinkedList *> &lists, char * filepath) {
    std::ifstream dataFile;
    dataFile.open(filepath);
    if (dataFile.is_open()) {
        // Get lines
        int lineCount;
        dataFile >> lineCount;
        std::string line, word, name1, name2;
        int cost, time;
        getline(dataFile, line);
        for(int i = 0; i < lineCount; i++) {
            getline(dataFile, line); // Take line of input

            // Take words from line
            std::istringstream ss(line);
            getline(ss, word, '|');  // First city name
            name1 = word;

            getline(ss, word, '|');  // Second city name
            name2 = word;

            getline(ss, word, '|');  // Cost
            cost = stoi(word);

            getline(ss, word, '|');  // Time
            time = stoi(word);

            // Add vertices and adjacent vertices for both cities (undirected graph)
            if(!list.contains(name1)) {
                // Add vertex
                Vertex * v = new Vertex(name1);
                vertices.push_back(v);
                list.add(v);
                LinkedList * linkedList = new LinkedList();
                lists.push_back(linkedList);
                v->setList(linkedList);
                //std::cout << "Added " << name1 << " to list.\n";
            }
            Vertex * v = new Vertex(name2, cost, time);
            adjacentVertices.push_back(v);
            list.get(name1)->getList()->add(v);
            //std::cout << "Added " << name2 << " as adjacent vertex to " << name1 << ".\n";
            if(!list.contains(name2)) {
                // Add vertex
                Vertex * v = new Vertex(name2);
                vertices.push_back(v);
                list.add(v);
                LinkedList * linkedList = new LinkedList();
                lists.push_back(linkedList);
                v->setList(linkedList);
                //std::cout << "Added " << name2 << " to list.\n";
            }
            v = new Vertex(name1, cost, time);
            adjacentVertices.push_back(v);
            list.get(name2)->getList()->add(v);
            //std::cout << "Added " << name1 << " as adjacent vertex to " << name2 << ".\n";
        }
        dataFile.close();
        return true;
    }
    else {
        return false;
    }
}

bool processFlightPlans(std::vector<flightPlan> &flights, char * filepath) {
    std::ifstream plansFile;
    plansFile.open(filepath);
    if (plansFile.is_open()) {
        // Get lines
        int lineCount;
        plansFile >> lineCount;
        std::string line, word, name1, name2;
        dataType type;
        getline(plansFile, line);
        for(int i = 0; i < lineCount; i++) {
            getline(plansFile, line); // Take line of input

            // Take words from line
            std::istringstream ss(line);
            getline(ss, word, '|');  // First city name
            name1 = word;

            getline(ss, word, '|');  // Second city name
            name2 = word;

            getline(ss, word, '|'); // Time or cost

            switch(word[0]) {
                case 'C': type = cost; break;
                case 'T': type = time; break;
            }

            flightPlan plan = {name1, name2, type};
            flights.push_back(plan);
        }
        plansFile.close();
        return true;
    }
    else {
        return false;
    }
};

int main(int argc, char *argv[]) {
    LinkedList adjacencyList;
    std::vector<Vertex *> vertices; // Stores all vertices for deletion
    std::vector<Vertex *> adjacentVertices; // Stores all adjacent vertices for deletion
    std::vector<LinkedList *> lists; // Stores all linked lists for deletion
    std::vector<flightPlan> flights;

    // Construct adjacency list
    if(!processFlightData(adjacencyList, vertices, adjacentVertices, lists, argv[1])) {
        std::cout << "Couldn't open flight data file.\n";
        return 1;
    }

    // Construct flight plans for output
    if(!processFlightPlans(flights, argv[2])) {
        std::cout << "Couldn't open flight plans file.\n";
        return 2;
    }

    DijkstraAlgorithm algorithm(adjacencyList);
    flightPlan current;
    int flightCount = 1;
    while(!flights.empty()) {
        current = flights.at(0);
        // Find source vertex in vertices vector, run algorithm and iterative backtracking
        for(int i = 0; i < vertices.size(); i++) {
            if(vertices.at(i)->getName() == current.from) {
                std::cout << "Flight " << flightCount++ << ": " << current.from << ", " << current.to;
                switch(current.type) {
                    case cost: std::cout << " (Cost)\n"; break;
                    case time: std::cout << " (Time)\n"; break;
                }
                algorithm.runAlgorithm(vertices.at(i), current.type);
                algorithm.printBestPath(current.to, current.type);
                algorithm.printIterativeBacktracking(current.to, current.type);
                i = vertices.size();
            }
        }
        std::cout << std::endl;
        flights.erase(flights.begin());
    }

    // Cleanup
    for(Vertex * v : vertices) {
        delete v;
    }
    for(Vertex * v : adjacentVertices) {
        delete v;
    }
    for(LinkedList * linkedList : lists) {
        delete linkedList;
    }

    return 0;
}
