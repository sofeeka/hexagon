//
// Created by Sonia on 23.05.2023.
//

#include "GameBoard.h"

GameBoard::GameBoard(int size)
  : size(size)
{
    initBoard();
}

void GameBoard::initBoard()
{
    Node* primaryNode = createNode();
    initLayer(primaryNode, 1, 1, 1 );
}

void GameBoard::initLayer( Node* parentNode, int qty1, int qty2, int qty3 )
{
    if( qty1 < this->size ) {
        Node *node1 = createNode();
        addConnection(parentNode, node1, AXIS_1);

        qty1++;
        initLayer( node1, qty1, qty2, qty3 );
    }

    if( qty2 < this->size * 2) {
        Node *node2 = createNode();
        addConnection(parentNode, node2, AXIS_2);

        qty2++;
        initLayer( node2, qty1, qty2, qty3);
    }

    if( qty3 < this->size) {
        Node *node3 = createNode();
        addConnection(parentNode, node3, AXIS_3);

        qty3++;
        initLayer( node3, qty1, qty2, qty3);
    }
}

void GameBoard::addConnection(Node *node1, Node *node2, Axis axis)
{
    node1->addConnectedNode(node2, axis, true);
    node2->addConnectedNode(node1, axis, false);
}

Node* GameBoard::createNode() {
    Node* node = new Node;
    this->nodes.push_back(node);
    return node;
}

