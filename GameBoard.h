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

    void initBoard();
    void addConnection(Node* node1, Node* node2, Axis axis );
    void initLayer( Node* parentNode, int qty1, int qty2, int qty3 );

public:
    GameBoard(int size);


    Node *createNode();
};



#endif //PJC_GAMEBOARD_H
