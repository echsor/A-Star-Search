#ifndef READGRAPH_H
#define READGRAPH_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>

#include "Node.h"

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
std::map<std::string, std::vector<std::string>> buildGraph(const std::string &path, GraphEdgeType graphEdgeType);


#endif //READGRAPH_H
