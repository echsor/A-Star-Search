#include <iostream>
#include "ReadGraph.h"

int main() {
    std::map<std::string, std::vector<std::string>> g = buildGraph("graphs/graph1.txt", GraphEdgeType::undirected);
    for (const auto& [k, vec]: g) {
        std::cout << "node = " << k << " has neighbors =";
        for (const auto &neighbor: vec) {
            std::cout << " " << neighbor;
        }
        std::cout << std::endl;
    }


}
