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

    for (int i = 0; i < 9; ++i) {
        vec.push_back(createNode());
    }

    addVerticalConnections(vec);

    initSide(vec, true);
    initSide(vec, false);

    std::cout << nodes.size() <<"\n";
}

void GameBoard::initSide(std::vector<Node*> vec, bool left )
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

void GameBoard::addConnection(Node *node1, Node *node2, Axis axis) // static
{
    node1->addConnectedNode(node2, axis, true);
    node2->addConnectedNode(node1, axis, false);
}
void GameBoard::addVerticalConnections(std::vector<Node *> vec) // static
{
    for (int i = 0; i < vec.size() - 1; ++i) {
        addConnection(vec[i], vec[i+1], AXIS_2);
    }
}


Node* GameBoard::createNode() {
    Node* node = new Node();
    this->nodes.push_back(node);
    return node;
}

