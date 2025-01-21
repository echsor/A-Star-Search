#ifndef READGRAPH_H
#define READGRAPH_H

#include <string>
#include <unordered_map>

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
 * @return The adjacency list.
 */
std::unordered_map<std::string, std::unordered_map<std::string, int>> readGraph(const std::string &path);


#endif //READGRAPH_H
