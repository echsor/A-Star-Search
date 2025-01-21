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

/**
 * A node for the A-Star search algorithm.
 * @tparam T The type of the node's identifier.
 */
template<typename T>
struct AStarNode {
    T identifier{};
    int costToHere{};
};

/**
 * A frontier keeps track of nodes on the frontier. Nodes on the frontier are those that we know about, but
 * we have yet to explore them. Once a nodes is explored it leaves the frontier. Nodes in the frontier have
 * an order: They are ordered by the lowest total predicted cost to the goal. The total predicted cost to the
 * goal is determined as <b>known cost from start to node + heuristic cost from node to goal</b>. Nodes
 * that are already on the frontier will be updated if a path with a lower predicted cost exists.
 * @tparam T The type for the node identifier.
 */
template<typename T>
class Frontier {
    std::vector<AStarNode<T>> frontier{};

    const std::map<std::string, int> &nodeToHeuristic{}; // a map of node to heuristic value

public:
    /**
     * Create a Frontier object that will keep track of nodes on the frontier.
     * @param nodeToHeuristic
     */
    explicit Frontier(const std::map<std::string, int> &nodeToHeuristic) : nodeToHeuristic(nodeToHeuristic) {
    }

    /**
     * Determine if there are any nodes left in the frontier.
     * @return True if there are no nodes left in the frontier, else false.
     */
    [[nodiscard]] bool empty() const {
        return frontier.empty();
    }

    /**
     * Gets the next node to explore from the frontier. Next node to explore will have the lowest total
     * predicted cost to the goal node. Removes the node from the frontier.
     * Undefined behaviour when called on empty frontier.
     * @return The frontier node to explore.
     */
    [[nodiscard]] AStarNode<T> getNextNodeToExplore() {
        auto toReturn = frontier.back();
        frontier.pop_back();
        return toReturn;
    }

    /**
     * Get an iterator to a node on the frontier.
     * @param nodeIdentifier To node for which to get an iterator to.
     * @return An optional object containing the iterator to the node if the node exists on the frontier, else
     * the optional will not have a value.
     */
    [[nodiscard]] std::optional<typename std::vector<AStarNode<T>>::iterator> getNodeIt(const T &nodeIdentifier) {
        auto it = frontier.begin();
        for (; it < frontier.end(); ++it) {
            if (it->identifier == nodeIdentifier) {
                return it;
            }
        }
        return {};
    }

    /**
     * Remove the frontier node at the iterator.
     * @param it The iterator pointing to the node to remove.
     */
    void removeNodeIt(const typename std::vector<AStarNode<T>>::iterator it) {
        frontier.erase(it);
    }

    /**
     * Add a new node to the frontier.
     * Assumes no node on the frontier already uses the identifier.
     * @param nodeToAdd The node to add to the frontier. Must have a unique identifier, but this isn't checked.
     * @param totalCost The total cost (known cost + heursitic cost) from start to goal for this node.
     */
    void addNode(AStarNode<T> nodeToAdd, const int totalCost) {
        auto it = std::lower_bound(frontier.begin(), frontier.end(), totalCost,
                                   [this](const AStarNode<T> &other, const int totalCostLambda) {
                                       return other.costToHere + nodeToHeuristic.at(other.identifier) > totalCostLambda;
                                   });
        frontier.insert(it, nodeToAdd);
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
 * @param nodeToHeuristic The heuristic values for each node. Estimated cost to goal from a node.
 * @return The path to the goal node if found.
 */
template<typename T>
std::optional<std::vector<T>> aStarSearch(const T &start, const T &goal,
                                          const std::unordered_map<T, std::unordered_map<T, int>> &graph,
                                          const std::map<T, int> nodeToHeuristic) {
    // not going anywhere
    if (goal == start) {
        return {{start}};
    }

    Frontier<T> frontier{nodeToHeuristic};
    std::unordered_set<T> visited{};
    std::unordered_map<T, std::optional<T>> nodeToParent{}; // node and their parent

    frontier.addNode({start, 0}, nodeToHeuristic.at(start));
    nodeToParent[start] = {};

    while (!frontier.empty()) {
        auto [nodeToExploreIdentifier, nodeToExploreCost] = frontier.getNextNodeToExplore();

        // We found the goal node! Build the path from start to the goal.
        if (nodeToExploreIdentifier == goal) {
            std::vector<T> pathToGoal{goal};
            while (nodeToParent.at(pathToGoal.back()).has_value()) {
                pathToGoal.push_back(nodeToParent.at(pathToGoal.back()).value());
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
                                           + nodeToHeuristic.at(neighborNodeIdentifier);
            // this neighbor node is already on the frontier
            if (auto opt_it = frontier.getNodeIt(neighborNodeIdentifier); opt_it.has_value()) {
                const int existingNeighborCostToGoal = opt_it.value()->costToHere
                                                       + nodeToHeuristic.at(neighborNodeIdentifier);
                if (neighborCostToGoal < existingNeighborCostToGoal) {
                    frontier.removeNodeIt(opt_it.value());
                } else {
                    continue;
                }
            }
            // neighbor was not on frontier, or we found a cheaper path to the neighbor
            frontier.addNode({neighborNodeIdentifier, costToNeighbor}, neighborCostToGoal);
            nodeToParent[neighborNodeIdentifier] = nodeToExploreIdentifier;
        }
    }
    return {};
}

#endif //ASTAR_H
