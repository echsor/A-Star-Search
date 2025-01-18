#ifndef ASTAR_H
#define ASTAR_H
#include <optional>
#include <queue>
#include <set>
#include <vector>

#include "Node.h"

/**
 * Like a Node but with some extra information relevant to the A-Star search algorithm.
 * @tparam T The type of the Node's value parameter.
 */
template<typename T>
struct AStarNode {
    int cheapestKnownCostFromStartToHere{}; // g(n)
    const int heuristicCostToGoal{}; // h(n)

    AStarNode<T> *parent{nullptr};

    Node<T> node{};

    bool operator<(const AStarNode &other) const {
        const double thisTotalCost = cheapestKnownCostFromStartToHere + heuristicCostToGoal;
        const double otherTotalCost = other.cheapestKnownCostFromStartToHere + other.heuristicCostToGoal;
        return thisTotalCost < otherTotalCost;
    }
};

/**
 * Run A-Star search. Start at the given start node and attempts to find the goal node. A-Star is optimal (finds the
 * cheapest path to the goal) if the heuristic used is consistent. Consistent: for each edge the heuristic cannot drop
 * more than the edge weight.
 * @tparam T The type of the Node's value parameter.
 * @param start The node to start the search from.
 * @param goal The goal node to attempt to find. Will be found if there is a path to it from the start.
 * @return The path to the goal node if found.
 */
template<typename T>
std::optional<std::vector<Node<T>>> aStarSearch(const Node<T> &start, const Node<T> &goal) {
    // AStarNode<T> startAStar;
    //
    // std::set<AStarNode<T>> frontier;




    return {};
}

#endif //ASTAR_H
