#include "ReadGraph.h"


std::unordered_map<std::string, std::unordered_map<std::string, int>> readGraph(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return {};
    }

    std::unordered_map<std::string, std::unordered_map<std::string, int>> adjacencyList;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string nodeIdentifier;
        // line is empty
        if (!(iss >> nodeIdentifier)) {
            continue;
        }

        auto [insertPos, insertSuccess] = adjacencyList.insert({nodeIdentifier, {}});

        std::string neighboringNodeIdentifier;
        int edgeWeight;
        while (iss >> neighboringNodeIdentifier >> edgeWeight) {
            insertPos->second.insert({neighboringNodeIdentifier, edgeWeight});
            adjacencyList.insert({neighboringNodeIdentifier, {}});
        }
    }

    file.close();

    return adjacencyList;
}
