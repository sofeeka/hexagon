//
// Created by Sonia on 23.05.2023.
//

#include <iostream>
#include "GameBoard.h"

GameBoard::GameBoard()
  : size(5)
{
    initBoard();
}

void GameBoard::initBoard()
{
    std::vector<Node*> vec;
    vec.reserve(9);

    for (int i = 0; i < 9; ++i) {
        vec.push_back(createNode());
    }

    addVerticalConnections(vec);

    initSide(vec, true);
    initSide(vec, false);

    std::cout << nodes.size() <<"\n";
}

void GameBoard::initSide(const std::vector<Node*>& vec, bool left )
{

    if ( vec.size() == size)
        return;

    std::vector<Node*> newVec;

    for (int i = 0; i < vec.size() - 1; ++i) {

        Node* node1 = vec[i];
        Node* node2 = vec[i + 1];
        Node* newNode = createNode();

        node1->addConnectedNode(newNode, AXIS_3, left);
        node2->addConnectedNode(newNode, AXIS_1, !left);

        newVec.push_back(newNode);
    }

    addVerticalConnections(newVec);
    initSide(newVec, left);
}

void GameBoard::addVerticalConnections(const std::vector<Node* >& vec) // static
{
    for (int i = 0; i < vec.size() - 1; ++i) {
        vec[i]->addConnectedNode(vec[i+1], AXIS_2, true);
        vec[i+1]->addConnectedNode(vec[i], AXIS_2, false);
    }
}

Node* GameBoard::createNode() {
    Node* node = new Node();
    this->nodes.push_back(node);
    return node;
}

