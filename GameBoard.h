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
    Node* selectedNode;
    std::vector< Node* > nodes;
    Node* createNode();

    bool gameFinished;

    void initBoard();
    void initSide(const std::vector<Node *>& vec, bool left);

    static void addVerticalConnections(const std::vector<Node* >& vec);

public:
    GameBoard();

    const std::vector<Node *> &getNodes() const;

    Node *getNodeByPosition(const Position &pos) const;

    void changeTurn();

    PlayerTurn getTurn() const;

    Node *getSelectedNode() const;

    void setSelectedNode(Node *s);

    static NodeState getNodeStateByPlayerTurn(PlayerTurn pt);

    int getNodeQtyByNodeState(NodeState ns) const;

    bool hasGameFinished() const;

    void setGameFinished(bool gameFinished);

    bool currentPlayerMoveIsPossible(PlayerTurn pt) const;

    NodeState getWinnerState() const;

    void finishGame() const;
};



#endif //PJC_GAMEBOARD_H
