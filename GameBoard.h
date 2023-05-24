//
// Created by Sonia on 23.05.2023.
//

#ifndef PJC_GAMEBOARD_H
#define PJC_GAMEBOARD_H

#include "Node.h"

class GameBoard
{
private:
    int size;
    std::vector< Node* > nodes;
    Node* createNode();

    void initBoard();
    void initSide(const std::vector<Node *>& vec, bool left);

    static void addVerticalConnections(const std::vector<Node* >& vec);

public:
    GameBoard();
};



#endif //PJC_GAMEBOARD_H
