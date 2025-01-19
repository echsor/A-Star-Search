#ifndef READGRAPH_H
#define READGRAPH_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <set>

#include "Node.h"

struct Edge {
    std::string destinationNodeIdentifier{};
    int edgeWeight{};

    bool operator<(const Edge &other) const {
        return destinationNodeIdentifier < other.destinationNodeIdentifier;
    }
};

enum class GraphEdgeType {
    undirected,
    directed
};

/**
 * Reads an adjacency list from a file.
 * @param path The path to the adjacency list
 * @param graphEdgeType The type of edges present in the graph.
 * @return The adjacency list.
 */
std::map<std::string, std::set<Edge>> readGraph(const std::string &path, const GraphEdgeType graphEdgeType);


#endif //READGRAPH_H
