//
// Created by Sonia on 23.05.2023.
//

#include <iostream>
#include "GameBoard.h"
#include <SFML/Graphics.hpp>

const Position startingPosition = Position(400, 75);

GameBoard::GameBoard()
  : size(5), turn(PlayerTurn::turnPLAYER1), selectedNode(nullptr)
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

            node->setPosition(x, y + Node::height + Node::margin);
        }
        vec.push_back(node);
    }

    vec[3]->setDisabled();
    vec.front()->setState(NodeState::nsPLAYER2);
    vec.back()->setState(NodeState::nsPLAYER1);

    addVerticalConnections(vec);

    initSide(vec, true);
    initSide(vec, false);

}

void GameBoard::initSide(const std::vector<Node*>& vec, bool left )
{

    if ( vec.size() == size)
    {
        vec.front()->setState(NodeState::nsPLAYER1);
        vec.back()->setState(NodeState::nsPLAYER2);
        return;
    }

    std::vector<Node*> newVec;

    for (int i = 0; i < vec.size() - 1; ++i) {

        Node* node1 = vec[i];
        Node* node2 = vec[i + 1];
        Node* newNode = createNode();

        node1->addConnectedNode(newNode, AXIS_3, left);
        node2->addConnectedNode(newNode, AXIS_1, !left);
        newNode->addConnectedNode(node1, AXIS_3, !left);
        newNode->addConnectedNode(node2, AXIS_1, left);

        int x = left ?
                node1->getX() - ( Node::width * 3 / 4 + Node::margin )
              : node1->getX() + ( Node::width * 3 / 4 + Node::margin );
        int y = ( node1->getY() + node2->getY() ) / 2;

        newNode->setPosition( x , y );

        newVec.push_back(newNode);
    }

    if(newVec.size() == 8)
        newVec[4]->setDisabled();

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

const std::vector<Node *> &GameBoard::getNodes() const {
    return nodes;
}

Node* GameBoard::getNodeByPosition(const Position& pos) const
{
    auto it = std::find_if(nodes.begin(), nodes.end(), [pos](Node* node)
    {
       return node->isClicked(pos);
    });

    if (it == nodes.end())
        return nullptr;

    return *it;

}

void GameBoard::changeTurn()
{
    this->turn = turn == turnPLAYER1 ? turnPLAYER2 : turnPLAYER1;
    setSelectedNode(nullptr);
}

PlayerTurn GameBoard::getTurn() const {
    return turn;
}

Node *GameBoard::getSelectedNode() const {
    return selectedNode;
}

void GameBoard::setSelectedNode(Node *s) {
    selectedNode = s;
}

NodeState GameBoard::getNodeStateByPlayerTurn(PlayerTurn pt)
{
    return pt == turnPLAYER1 ? nsPLAYER1 : nsPLAYER2;
}