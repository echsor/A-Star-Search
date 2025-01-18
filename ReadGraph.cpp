#include "ReadGraph.h"


std::map<std::string, std::vector<std::string>> buildGraph(const std::string &path, const GraphEdgeType graphEdgeType) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return {};
    }

    std::map<std::string, std::vector<std::string>> adjacencyList;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string nodeIdentifier;
        if (!(iss >> nodeIdentifier)) {
            continue;
        }

        auto [insertPos, insertSuccess] = adjacencyList.insert({nodeIdentifier, {}});

        std::string nodeLinkedToIdentifier;
        while (iss >> nodeLinkedToIdentifier) {
            insertPos->second.push_back(nodeLinkedToIdentifier);
            adjacencyList.insert({nodeLinkedToIdentifier, {}});
        }
    }

    file.close();

    return adjacencyList;
}
