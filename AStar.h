#ifndef ASTAR_H
#define ASTAR_H
#include <map>
#include <unordered_map>
#include <optional>
#include <queue>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>

#include "ReadGraph.h"


template<typename T>
struct AStarNode {6
    T identifier{};
    int costToHere{};
};

template<typename T>
class Frontier {
    std::vector<AStarNode<T>> frontier{};

    const std::map<std::string, int> &heuristicMap{};

public:
    explicit Frontier(const std::map<std::string, int> &heuristicMap) : heuristicMap(heuristicMap) {
    }

    [[nodiscard]] bool empty() const {
        return frontier.empty();
    }

    /**
     * Gets the next node to explore from the frontier. Next node to explore will have the lowest estimated
     * cost to the goal node. Removes the node from the frontier.
     * Undefined behaviour when called on empty frontier.
     * @return The frontier node to explore.
     */
    [[nodiscard]] AStarNode<T> getNextNodeToExplore() {
        auto toReturn = frontier.back();
        frontier.pop_back();
        return toReturn;
    }

    [[nodiscard]] std::optional<typename std::vector<AStarNode<T>>::iterator> getNodeIt(const T &nodeIdentifier) {
        auto it = frontier.begin();
        for (; it < frontier.end(); ++it) {
            if (it->identifier == nodeIdentifier) {
                return it;
            }
        }
        return {};
    }

    void removeNodeIt(const typename std::vector<AStarNode<T>>::iterator it) {
        frontier.erase(it);
    }


    void addNode(AStarNode<T> nodeToAdd, const int totalCost) {
        auto it = std::lower_bound(frontier.begin(), frontier.end(), totalCost,
                                   [this](const AStarNode<T> &other, const int totalCostLambda) {
                                       return other.costToHere + heuristicMap.at(other.identifier) > totalCostLambda;
                                   });
        frontier.insert(it, nodeToAdd);
    }

    void changeNode(const AStarNode<T> newNode, const int totalCost) {
        removeNodeIt(getNodeIt(newNode.first));
        addNode(newNode, totalCost);
    }
};

/**
 * Run A-Star search. Start at the given start node and attempts to find the goal node. A-Star is optimal (finds the
 * cheapest path to the goal) if the heuristic used is consistent. Consistent: for each edge the heuristic cannot drop
 * more than the edge weight.
 * @tparam T The type of the Node's value parameter.
 * @param start The node to start the search from.
 * @param goal The goal node to attempt to find. Will be found if there is a path to it from the start.
 * @param graph The graph to search for a path from start to goal.
 * @param heuristicMap The heuristic values for each node. Estimated cost to goal from a node.
 * @return The path to the goal node if found.
 */
template<typename T>
std::optional<std::vector<T>> aStarSearch(const T &start, const T &goal,
                                          const std::unordered_map<T, std::unordered_map<T, int>> &graph,
                                          const std::map<T, int> heuristicMap) {
    // not going anywhere
    if (goal == start) {
        return {{start}};
    }

    Frontier<T> frontier{heuristicMap};
    std::unordered_set<T> visited{};
    std::unordered_map<T, std::optional<T>> parents{}; // node and their parent

    frontier.addNode({start, 0}, heuristicMap.at(start));
    parents[start] = {};


    while (!frontier.empty()) {
        // get next node to explore
        auto [nodeToExploreIdentifier, nodeToExploreCost] = frontier.getNextNodeToExplore();

        // We found the goal node! Build the path from start to the goal.
        if (nodeToExploreIdentifier == goal) {
            std::vector<T> pathToGoal{goal};
            while (parents.at(pathToGoal.back()).has_value()) {
                pathToGoal.push_back(parents.at(pathToGoal.back()).value());
            }
            std::reverse(pathToGoal.begin(), pathToGoal.end());
            return pathToGoal;
        }

        // explore the current node's neighbors
        for (const auto &[neighborNodeIdentifier, neighborEdgeWeight]:
             graph.at(nodeToExploreIdentifier)) {

            // only consider unvisited nodes and skip cycles
            if (visited.contains(neighborNodeIdentifier) || neighborNodeIdentifier == nodeToExploreIdentifier) {
                continue;
            }
            const int costToNeighbor = nodeToExploreCost
                                       + graph.at(nodeToExploreIdentifier).at(neighborNodeIdentifier);
            const int neighborCostToGoal = costToNeighbor
                                           + heuristicMap.at(neighborNodeIdentifier);
            // this neighbor node is already on the frontier
            if (auto opt_it = frontier.getNodeIt(neighborNodeIdentifier); opt_it.has_value()) {
                const int existingNeighborCostToGoal = opt_it.value()->costToHere
                                                       + heuristicMap.at(neighborNodeIdentifier);
                if (neighborCostToGoal < existingNeighborCostToGoal) {
                    frontier.removeNodeIt(opt_it.value());
                } else {
                    continue;
                }
            }
            // neighbor was not on frontier, or we found a cheaper path
            frontier.addNode({neighborNodeIdentifier, costToNeighbor}, neighborCostToGoal);
            parents[neighborNodeIdentifier] = nodeToExploreIdentifier;
        }
    }
    return {};
}


#endif //ASTAR_H
