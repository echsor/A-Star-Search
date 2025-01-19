#include <iostream>
#include "ReadGraph.h"
#include "ReadHeuristic.h"

int main() {
    auto g = readGraph("graphs/graph1.txt", GraphEdgeType::undirected);
    for (const auto& [nodeIdentifier, edges]: g) {
        std::cout << "node = " << nodeIdentifier << " has neighbors =";
        for (const auto &[destinationNodeIdentifier, edgeWeight]: edges) {
            std::cout << " (" << destinationNodeIdentifier << ", " << edgeWeight << ")";
        }
        std::cout << std::endl;
    }

    std::map<std::string, int> h = readHeuristic("graphs/heuristic1.txt");
    for (const auto &[nodeIdentifier, heuristicValue] : h) {
        std::cout << "node = " << nodeIdentifier << " has heuristic value " << heuristicValue << std::endl;
    }
}
