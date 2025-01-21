#ifndef READHEURISTIC_H
#define READHEURISTIC_H
#include <map>
#include <string>
#include <iostream>

/**
 * Reads in the heuristic information from a file. Each node has a heuristic
 * that represents the estimated cost from the node the goal node.
 *
 * Each line is for a node and its associated heuristic value.
 * The expected format of the graph is as follows:
 * nodeIdentifier heuristicWeight
 *
 * Types:
 * nodeIdentifier  (string)
 * heuristicWeight (int)
 *
 * For example:
 * S 40
 * A 23
 * G 0
 * Means that there three nodes. S has a heuristic value of 40.
 * A has a heuristic value of 23. G has a heuristic value of 0
 * which indicates that it is the goal node (not that that information
 * is encoded here in any way).
 *
 * @param path The file to load the heuristic information from.
 * @return A map of node to the heuristic value.
 */
std::map<std::string, int> readHeuristic(const std::string &path);

#endif //READHEURISTIC_H
