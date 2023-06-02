//
// Created by Sonia on 23.05.2023.
//

#ifndef PJC_GAMEBOARD_H
#define PJC_GAMEBOARD_H

#include "Node.h"
#include <SFML/Graphics.hpp>

/**
 * @brief Enum representing whose turn it is to make a move.
 */
enum PlayerTurn{
    turnPLAYER1, /*!< Enum value turnPLAYER1. Always human. */
    turnPLAYER2  /*!< Enum value turnPLAYER2. Either a computer or human. */
};

/**
 * @class GameBoard
 *
 * @brief Represents a game board with nodes and game logic.
 *
 * The GameBoard class represents a playing field consisting of nodes. It manages the game state,
 * player turns, moves, and game completion. It also provides functions to interact with the nodes
 * and retrieve information about the state of the game board.
*/
class GameBoard
{
private:
    int size; /*!< Integer size representing length of the side of a board. */
    PlayerTurn turn; /*!< Enum representing whose turn it is. */
    bool playingAgainstComputer; /*!< Bool value, shows wether the game is played against a computer or human. */

    Node* selectedNode; /*!< Bool value representing a node which was selected to be moved by either of players. */
    std::vector< Node* > nodes; /*!< Vector containing all created nodes in a natural order of creation. */

    /** Creates a new node and adds it to the game board std::vector<Node*> nodes. */
    Node* createNode();

    /**
     * @brief Initializes the game board with nodes and connections.
     *
     * The initBoard function is responsible for initializing the game board by creating nodes and
     * establishing connections between them. We form the main vertical axis and go te the sides
     * connecting two neighbouring nodes to form the game board.
     */
    void initBoard();

    /**
     * @brief Initializes one side of the game board with nodes and connections.
     *
     * The initSide function is a private member function of the GameBoard class.
     * It is called by initBoard to initialize one side of the game board, either the left or the right side.
     * This function creates new nodes and sets connections with the existing nodes to form a side of the board.
     *
     * @param vec The vector of nodes representing the last vec of the side of the board we are going from.
     * @param left Specifies whether the side being initialized is the left side or the right one.
     */
    void initSide(const std::vector<Node *>& vec, bool left);

    /**
     * @brief Adds vertical connections between nodes.
     *
     * The addVerticalConnections function is a private static member function of the GameBoard class.
     * It is called by initBoard and initSide to add vertical connections between nodes on vertical axis.
     *
     * @param vec The vector of nodes representing the current side of the board.
     */
    static void addVerticalConnections(const std::vector<Node* >& vec);

public:
/**
 * @brief Default constructor for the GameBoard class.
 *
 * The GameBoard constructor creates a new instance of the GameBoard class and calls InitBoard() function.
 * It sets the size of the game board to 5, the initial player turn to PlayerTurn::turnPLAYER1.
 * and the selectedNode pointer to nullptr.
 */
GameBoard();
/**
 * @brief Copy constructor for the GameBoard class.
 *
 * The GameBoard copy constructor creates a new instance of the GameBoard class by making a deep copy of an existing game board.
 * It copies the size, player turn, and selected node from the source game board.
 * It then creates new nodes and copies the state of each node from the source game board.
 *
 * @param gameBoard The game board to be copied.
 */
GameBoard(const GameBoard& gameBoard);
/**
 * @brief Destructor for the GameBoard class.
 *
 * The virtual destructor for the GameBoard class is responsible for freeing the memory allocated for the nodes in the game board.
 * It iterates through the vector of nodes and deletes each node.
 */
virtual ~GameBoard();

// nodes

/**
 * @brief Gets the vector of nodes on the game board.
 *
 * This function returns a constant reference to the vector of nodes of the game board.
 *
 * @return const std::vector<Node*>& The vector of nodes of the game board in natural order of creation.
 */
const std::vector<Node *> &getNodes() const;

/**
 * @brief Sets the selected node on the game board.
 *
 * The setSelectedNode function sets the specified node as the currently selected node on the game board.
 *
 * @param s A pointer to the node to be set as the selected node.
 */
void setSelectedNode(Node *s);

/**
 * @brief Retrieves the currently selected node on the game board.
 *
 * The getSelectedNode function returns a pointer to the currently selected node on the game board.
 *
 * @return A pointer to the currently selected node, or nullptr if no node is currently selected.
 */
Node* getSelectedNode() const;

/**
 * @brief Retrieves a specific node on the game board based on its position.
 *
 * The getNodeByPosition function searches for a node on the game board that matches the specified position.
 *
 * @param pos The position of the node to be retrieved.
 * @return A pointer to the node at the specified position, or nullptr if no matching node was found.
 */
Node* getNodeByPosition(const Position &pos) const;

/**
 * @brief Retrieves the node state enum based on the player turn.
 *
 * The getNodeStateByPlayerTurn function returns the corresponding node state based on the specified player turn.
 *
 * @param pt The player turn for which to retrieve the node state.
 * @return The node state corresponding to the specified player turn.
 */
static NodeState getNodeStateByPlayerTurn(PlayerTurn pt);

/**
 * @brief Retrieves the quantity of nodes with a specific node state.
 *
 * The getNodeQtyByNodeState function counts the number of nodes of the game board that have the specified node state.
 *
 * @param ns The node state for which to count the nodes.
 * @return The quantity of nodes with the specified node state.
 */
int getNodeQtyByNodeState(NodeState ns) const;

/**
 * @brief Retrieves a vector of nodes with a specific node state.
 *
 * The getNodesByNodeState function returns a vector containing pointers to all nodes of the game board that have the specified node state.
 *
 * @param ns The node state for which to retrieve the nodes.
 * @return A vector of nodes with the specified node state.
 */
std::vector<Node *> getNodesByNodeState(NodeState ns) const;

/**
 * @brief Retrieves the index of a node on the game board.
 *
 * The getNodeIndex function returns the index of the specified node on the game board.
 *
 * @param node A pointer to the node for which to retrieve the index.
 * @return The index of the specified node, or -1 if the node is not found.
 */
int getNodeIndex(const Node* node) const;
/**
 * @brief Retrieves a node on the game board based on its index.
 *
 * The getNodeByIndex function returns a pointer to the node at the specified index on the game board.
 *
 * @param index The index of the node to be retrieved.
 * @return A pointer to the node at the specified index, or nullptr if the index is out of range.
 */
Node* getNodeByIndex(const int index) const;

// turn

/**
 * @brief Changes the current player's turn.
 *
 * The changeTurn function changes the current player's turn to the opposite player.
 * It also checks if the current player has any possible moves left.
 *
 * @return True if the turn was successfully changed, false if the current player has no possible moves.
 */
bool changeTurn();

/**
 * @brief Retrieves the current player's turn.
 *
 * The getTurn function returns the current player's turn.
 *
 * @return The current player's turn.
 */
PlayerTurn getTurn() const;

/**
 * @brief Sets the current player's turn.
 *
 * The setTurn function sets the current player's turn to the specified value.
 *
 * @param turn The player turn to be set.
 */
void setTurn(PlayerTurn turn);

/**
 * @brief Retrieves the opposite player's turn.
 *
 * The getOppositeTurn function returns the opposite player's turn based on the specified player turn.
 *
 * @param pt The player turn for which to retrieve the opposite turn.
 * @return The opposite player's turn.
 */
static PlayerTurn getOppositeTurn(PlayerTurn pt);

// game state

/**
 * @brief Checks if the current player has any possible moves.
 *
 * The currentPlayerMoveIsPossible function checks if the current player specified by 'pt'
 * has any possible moves left on the game board.
 *
 * @param pt The player turn to check for possible moves.
 * @return True if the current player has possible moves, false otherwise.
 */
bool currentPlayerMoveIsPossible(PlayerTurn pt) const;

/**
 * @brief Checks if the game is being played against a computer.
 *
 * The isPlayingAgainstComputer function checks if the game is being played against a computer opponent.
 *
 * @return True if the game is being played against a computer, false otherwise.
 */
bool isPlayingAgainstComputer() const;

/**
 * @brief Sets whether the game is being played against a computer.
 *
 * The setPlayingAgainstComputer function sets the playingAgainstComputer variable to indicate
 * whether the game is being played against a computer opponent.
 *
 * @param playingAgainstComputer True if the game is being played against a computer, false otherwise.
 */
void setPlayingAgainstComputer(bool playingAgainstComputer);

// move

/**
 * @brief Moves a game piece from one node to another.
 *
 * The move function moves a game piece from the node specified by 'nodeFrom' to the node specified by 'nodeTo'.
 * It checks the validity of the move and updates the game state accordingly.
 *
 * @param nodeFrom The node from which the game piece is being moved.
 * @param nodeTo The node to which the game piece is being moved.
 * @return True if the move was successful and it resulted in a change of turn, false otherwise.
 */
bool move(Node* nodeFrom, Node* nodeTo) const;

// finish game

/**
 * @brief Finishes the game and updates the game state.
 *
 * The finishGame function is called when the game is over. It updates the game state
 * by assigning the winning state to all remaining empty nodes.
 */
void finishGame() const;

/**
 * @brief Retrieves the winning state of the game.
 *
 * The getWinnerState function returns the NodeState of the winning player.
 *
 * @return The NodeState of the winning player.
 */
NodeState getWinnerState() const;

/**
 * @brief Retrieves the winning state based on points.
 *
 * The getWinnerByPoints function determines the winning state based on the points
 * gained by each player. It returns the NodeState of the player with bigger amount of points.
 *
 * @return The NodeState of the winning player based on points quantity.
 */
NodeState getWinnerByPoints() const;

/**
 * @brief Retrieves the winning points quantity.
 *
 * The getWinningPointsQty function calculates and returns the difference in points between
 * the current player and the opponent player.
 *
 * @return The winning points quantity (positive if current player has more points, negative otherwise).
 */
int getWinningPointsQty() const;
};

#endif //PJC_GAMEBOARD_H
