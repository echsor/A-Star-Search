#include <iostream>
#include "ReadGraph.h"
#include "ReadHeuristic.h"

int main() {
    std::map<std::string, std::vector<std::string>> g = readGraph("graphs/graph1.txt", GraphEdgeType::undirected);
    for (const auto& [k, vec]: g) {
        std::cout << "node = " << k << " has neighbors =";
        for (const auto &neighbor: vec) {
            std::cout << " " << neighbor;
        }
        std::cout << std::endl;
    }

    std::map<std::string, int> h = readHeuristic("graphs/heuristic1.txt");
    for (const auto &[nodeIdentifier, heuristicValue] : h) {
        std::cout << "node = " << nodeIdentifier << " has heuristic value " << heuristicValue << std::endl;
    }
}
