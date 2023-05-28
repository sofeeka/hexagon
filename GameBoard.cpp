//
// Created by Sonia on 23.05.2023.
//

#include <iostream>
#include "GameBoard.h"
#include <SFML/Graphics.hpp>

const float radius = 20;
const Position startingPosition = Position(400, 20);

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
        Node* node = createNode();
        if ( i == 0)
            node->setPosition(startingPosition);
        else
        {
            float x = vec[ i - 1 ]->getX();
            float y = vec[ i - 1 ]->getY();

            node->setPosition(x, y + 2 * radius * 1.5);
        }
        vec.push_back(node);
    }

    vec[3]->setEnabled(false);

    addVerticalConnections(vec);

    initSide(vec, true);
    initSide(vec, false);

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

        float x = left ? node1->getX() - radius * 1.5 : node1->getX() + radius * 1.5;
        float y = node1->getY() + radius * 1.5;

        newNode->setPosition( x , y );

        newVec.push_back(newNode);
    }

    if(newVec.size() == 8)
        vec[4]->setEnabled(false);

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

void GameBoard::assignCoordinates(std::vector<Node*>& vec, int row, int col, float startX, float startY, float offset)
{
    for (size_t i = 0; i < vec.size(); ++i) {
        Node* node = vec[i];
        float x = startX + (col * offset);
        float y = startY + (row * offset);
        node->setPosition(x, y);
        ++col;

        if (col > 2) {
            col = 0;
            ++row;
        }
    }
}

void GameBoard::displayCoordinates(const std::vector<Node*>& vec)
{
    for (size_t i = 0; i < vec.size(); ++i) {
        Node* node = vec[i];
        float x = node->getPosition().x;
        float y = node->getPosition().y;
        std::cout << "Node " << i << " - Coordinates: (" << x << ", " << y << ")" << std::endl;
    }
}


Node* GameBoard::createNode() {
    Node* node = new Node();
    this->nodes.push_back(node);
    return node;
}

const std::vector<Node *> &GameBoard::getNodes() const {
    return nodes;
}

std::vector< Node* > getVerticalNodes(Node* node)
{
    std::vector< Node* > vec;

    while(true)
    {
        vec.push_back( node );
    }
}