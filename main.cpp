#include <iostream>
#include "ReadGraph.h"
#include "ReadHeuristic.h"
#include "AStar.h"

int main() {
    auto g = readGraph("graphs/graph2.txt");
    for (const auto& [nodeIdentifier, edges]: g) {
        std::cout << "node = " << nodeIdentifier << " has neighbors =";
        for (const auto &[destinationNodeIdentifier, edgeWeight]: edges) {
            std::cout << " (" << destinationNodeIdentifier << ", " << edgeWeight << ")";
        }
        std::cout << std::endl;
    }

    std::map<std::string, int> h = readHeuristic("graphs/heuristic2.txt");
    for (const auto &[nodeIdentifier, heuristicValue] : h) {
        std::cout << "node = " << nodeIdentifier << " has heuristic value " << heuristicValue << std::endl;
    }

    if (auto opt_pathToGoal = aStarSearch<std::string>("S", "G", g, h); opt_pathToGoal.has_value()) {
        std::cout << "Path found" << std::endl;
        for (const std::string &node : opt_pathToGoal.value()) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Path not found" << std::endl;
    }
}
