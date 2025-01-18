#include "ReadGraph.h"


std::map<std::string, std::set<std::string>> readGraph(const std::string &path, const GraphEdgeType graphEdgeType) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return {};
    }

    std::map<std::string, std::set<std::string>> adjacencyList;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string nodeIdentifier;
        if (!(iss >> nodeIdentifier)) { // line is empty
            continue;
        }

        auto [insertPos, insertSuccess] = adjacencyList.insert({nodeIdentifier, {}});

        std::string neighboringNodeIdentifier;
        while (iss >> neighboringNodeIdentifier) {
            insertPos->second.insert(neighboringNodeIdentifier);
            adjacencyList.insert({neighboringNodeIdentifier, {}});
        }
    }

    file.close();

    return adjacencyList;
}
