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
};



#endif //PJC_GAMEBOARD_H
