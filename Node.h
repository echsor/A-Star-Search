#ifndef NODE_H
#define NODE_H
#include <vector>
#include <span>

template<typename T>
class Node {
private:
    mutable std::vector<T> neighbors{};

public:
    const T identifier{};

    /**
     * Constructor.
     * @param identifier The unique identifier of the node.
     * @param neighbors All the nodes to which this node has an edge.
     */
    Node(T identifier, std::vector<T> neighbors) : identifier(identifier), neighbors(neighbors) {
    }


    std::span<const T> getNeighbors() const {
        return std::span<const T>{neighbors.data(), neighbors.size()};
    }


    /**
     * Add an edge from this node to the input node. Does not add a symmetric edge. If the neighbor already exists
     * this function does nothing.
     * @param toAdd The node which is now a neighbour of this node.
     * @return True if a neighbor was added, false if not.
     */
    bool addNeighbor(Node *toAdd) {
        // neighbors.insert(toAdd);
        auto posToInsert = std::lower_bound(neighbors.begin(), neighbors.end(), toAdd);
        if (*posToInsert != toAdd) {
            // only add as neighbor if it isn't already one
            neighbors.insert(posToInsert, toAdd);
            return true;
        }
        return false;
    }

    /**
     * Removes a node as the neighbor if it exists.
     * @param toRemove The identifier of the node to remove as a neighbor of this node.
     * @return True if a neighbor was removes, false if not.
     */
    bool removeNeighbor(T &toRemove) {
        auto posToRemove = std::lower_bound(neighbors.begin(), neighbors.end(), toRemove,
                                            [](const Node &node, T &toRemove) {
                                                return node.identifier < toRemove;
                                            });
        if (*posToRemove != toRemove) {
            // only delete neighbor if it exists
            neighbors.erase(posToRemove);
            return true;
        }
        return false;
    }

    /**
     * @return How many neighbors this node has. If this node has an edge to itself that counts as a neighbor.
     */
    [[nodiscard]] std::size_t numNeighbors() const {
        return neighbors.size();
    }


    /**
     * Nodes are compared by their identifier.
     * @param other The other node to compare to.
     * @return True if this node is less than the other node, else false.
     */
    bool operator<(const Node<T> &other) const {
        return identifier < other.identifier;
    }
};


#endif //NODE_H
