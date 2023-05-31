//
// Created by Sonia on 23.05.2023.
//

#ifndef PJC_GAMEBOARD_H
#define PJC_GAMEBOARD_H

#include "Node.h"
#include <SFML/Graphics.hpp>

enum PlayerTurn{
    turnPLAYER1,
    turnPLAYER2
};

class GameBoard
{
private:
    int size;
    PlayerTurn turn;
    bool playingAgainstComputer;
    Node* selectedNode;
    std::vector< Node* > nodes;
    Node* createNode();

    void initBoard();
    void initSide(const std::vector<Node *>& vec, bool left);

    static void addVerticalConnections(const std::vector<Node* >& vec);

public:
    GameBoard();
    GameBoard(const GameBoard& gameBoard);

    virtual ~GameBoard();

    // nodes
    const std::vector<Node *> &getNodes() const;

    void setSelectedNode(Node *s);

    Node *getSelectedNode() const;
    Node *getNodeByPosition(const Position &pos) const;

    static NodeState getNodeStateByPlayerTurn(PlayerTurn pt);
    int getNodeQtyByNodeState(NodeState ns) const;
    std::vector<Node *> getNodesByNodeState(NodeState ns) const;

    int getNodeIndex(const Node *node) const;
    Node *getNodeByIndex(const int index) const;

    // turn
    bool changeTurn();
    PlayerTurn getTurn() const;
    static PlayerTurn getOppositeTurn(PlayerTurn pt);

    // game state

    bool currentPlayerMoveIsPossible(PlayerTurn pt) const;

    // move
    bool move(Node *nodeFrom, Node *nodeTo) const;

    // finish game
    void finishGame() const;

    NodeState getWinnerState() const;
    NodeState getWinnerByPoints() const;

    int getWinningPointsQty() const;
};


#endif //PJC_GAMEBOARD_H

