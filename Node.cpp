//
// Created by Sonia on 23.05.2023.
//

#include "Node.h"

const float Node::height = 50;
const float Node::width = 75;
const float Node::margin = 1;

NodeConnection::NodeConnection(Node* node, Axis axis, bool down)
        : node(node), axis(axis), down(down) {}

Node::Node() : state(NodeState::nsEMPTY) {}

void Node::addConnectedNode(Node *node, Axis axis, bool down)
{
    NodeConnection nc(node, axis, down);
    connectedNodes.push_back(nc);
}

bool Node::isDisabled() const {
    return state == NodeState::nsDISABLED;
}

void Node::setDisabled() {
    state = NodeState::nsDISABLED;
}

Node* Node::getVerticalDownConnectedNode() const
{
    auto it = std::find_if( connectedNodes.begin(), connectedNodes.end(), [](const NodeConnection& nc)
    {
        return nc.axis == AXIS_2 && nc.down;
    });

    if (it == connectedNodes.end())
        return nullptr;

    return (*it).node;
}

const Position &Node::getPosition() const {
    return position;
}

void Node::setPosition(const Position &position) {
    this->position = position;
}

void Node::setPosition(float x, float y) {
    this->position = Position(x, y);
}

Position::Position(float x, float y) : x(x), y(y) {}

float Position::getX() const {
    return x;
}

float Position::getY() const {
    return y;
}

float Node::getX() const {
    return position.getX();
}

float Node::getY() const {
    return position.getY();
}

NodeState Node::getState() const {
    return state;
}

void Node::setState(NodeState state) {
    this->state = state;
}

bool Node::isClicked(const Position& clickedPos) const
{
    return abs(clickedPos.getX() - this->getX()) <= Node::width / 4
        && abs(clickedPos.getY() - this->getY()) <= Node::height / 2;

}

