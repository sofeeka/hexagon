//
// Created by Sonia on 23.05.2023.
//

#ifndef PJC_NODE_H
#define PJC_NODE_H

#include <vector>
#include <set>

/**
 * @brief Enum representing the axis of a node connection on the game board.
 */
enum Axis {
    AXIS_1, /*!< Enum value AXIS_1. Represents the left axis. */
    AXIS_2, /*!< Enum value AXIS_2. Represents the vertical axis. */
    AXIS_3  /*!< Enum value AXIS_3. Represents the right axis. */
};

/**
 * @brief Enum representing the state of a node.
 */
enum NodeState {
    nsEMPTY,    /*!< Enum value nsEMPTY. Represents an empty node. */
    nsPLAYER1,  /*!< Enum value nsPLAYER1. Represents a node occupied by PLAYER1. */
    nsPLAYER2,  /*!< Enum value nsPLAYER2. Represents a node occupied by PLAYER2. */
    nsDISABLED  /*!< Enum value nsDISABLED. Represents a disabled node. */
};

static const bool ONLY_EMPTY = true; /**< Static const used for functions which return nodes. */

class Node;

/**
 * @brief Struct representing a position with x and y coordinates.
 */
struct Position {
    int x; /*!< Integer representing the x-coordinate. */
    int y; /*!< Integer representing the y-coordinate. */

    /**
     * @brief Constructs a new Position object.
     *
     * @param x The x-coordinate. Default is 0.
     * @param y The y-coordinate. Default is 0.
     */
    Position(int x = 0, int y = 0);

/**
     * @brief Gets the x-coordinate.
     *
     * @return The x-coordinate.
     */
    int getX() const;

    /**
     * @brief Gets the y-coordinate.
     *
     * @return The y-coordinate.
     */
    int getY() const;};

/**
 * @brief Struct representing a connection between nodes.
 */
struct NodeConnection {
    Node* node; /*!< Pointer to the connected node. */
    Axis axis; /*!< Axis of the connection. */
    bool down; /*!< Flag indicating the direction of the connection. */

    /**
     * @brief Constructs a new NodeConnection object.
     *
     * @param node1 Pointer to the connected node.
     * @param axis1 Axis of the connection.
     * @param down1 Flag indicating the direction of the connection.
     */
    NodeConnection(Node* node1, Axis axis1, bool down1);
};

/**
 * @brief Class representing a node in the game board.
 */
class Node {
private:
    NodeState state; /*!< Current state of the node. */

public:
    /**
     * @brief Default constructor for Node.
     */
    Node();

    std::vector<NodeConnection> connectedNodes; /*!< Vector of connections to other nodes. */
    Position position; /*!< Position of the node on the game board. */

    static const int height; /*!< Height of the node. */
    static const int width; /*!< Width of the node. */
    static const int margin; /*!< Margin between the nodes. */

    // node
/**
 * @brief Adds a connected node to the current node.
 *
 * @param node The node to connect to.
 * @param axis The axis of the connection.
 * @param down Flag indicating the direction of the connection.
 */
    void addConnectedNode(Node* node, Axis axis, bool down);

/**
 * @brief Gets the set of connected nodes at level 1.
 *
 * @param onlyEmpty Flag indicating whether to include only empty nodes in the result.
 * @return The set of connected nodes at level 1.
 */
    std::set<Node*> getConnectedNodes_Level1(bool onlyEmpty = false) const;

/**
 * @brief Gets the set of empty connected nodes at level 2.
 *
 * @return The set of empty connected nodes at level 2.
 */
    std::set<Node*> getEmptyConnectedNodes_Level2() const;

    // position
/**
 * @brief Gets the position of the node.
 *
 * @return The position of the node.
 */
    const Position &getPosition() const;

/**
 * @brief Sets the position of the node.
 *
 * @param p The position to set.
 */
    void setPosition(const Position& p);

/**
 * @brief Sets the position of the node.
 *
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 */
    void setPosition(int x, int y);

/**
 * @brief Gets the x-coordinate of the node's position.
 *
 * @return The x-coordinate of the node's position.
 */
    int getX() const;

/**
 * @brief Gets the y-coordinate of the node's position.
 *
 * @return The y-coordinate of the node's position.
 */
    int getY() const;

    // state
/**
 * @brief Sets the state of the node.
 *
 * @param s The state to set.
 */
    void setState(NodeState s);

/**
 * @brief Gets the state of the node.
 *
 * @return The state of the node.
 */
    NodeState getState() const;

/**
 * @brief Sets the node as disabled.
 */
    void setDisabled();

/**
 * @brief Checks if the node is disabled.
 *
 * @return True if the node is disabled, false otherwise.
 */
    bool isDisabled() const;

/**
 * @brief Checks if the node is clicked based on the clicked position.
 *
 * @param clickedPos The position that was clicked.
 * @return True if the node is clicked, false otherwise.
 */
    bool isClicked(const Position& clickedPos) const;
};

#endif //PJC_NODE_H