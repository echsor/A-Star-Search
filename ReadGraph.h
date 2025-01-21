#ifndef READGRAPH_H
#define READGRAPH_H

#include <string>
#include <unordered_map>

/**
 * Reads in a graph from a file. Graph is considered directed. If you want an undirected graph add a
 * reflexive edge for each existing edge.
 *
 * Each line is for a node, with the edges and their corresponding weights listed afterwards.
 * The expected format of the graph is as follows:
 * nodeIdentifier [neighborNode weightEdgeToNeighborNode] ...
 *
 * Types:
 * nodeIdentifier           (string)
 * neighborNode             (string)
 * weightEdgeToNeighborNode (int)
 *
 * For example:
 * D F 30 H 23
 * ...
 * means that there is a node "D" that has 2 outgoing edges. An edge to "F" with weight 30. And an
 * edge to "H" with weight 23.
 *
 * Nodes that do not have any outgoing edges do not need a line. If another node has an edge to them
 * then they will show up as a node in a graph still.
 *
 * @param path The file to load the graph from.
 * @return A map of edges to a (map of neighbor edge and edge weight).
 */
std::unordered_map<std::string, std::unordered_map<std::string, int>> readGraph(const std::string &path);

#endif //READGRAPH_H
