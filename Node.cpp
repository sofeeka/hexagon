//
// Created by Sonia on 23.05.2023.
//

#include "Node.h"
#include <algorithm>
#include <cmath>

const int Node::height = 50;
const int Node::width = 75;
const int Node::margin = 2;

// public

// node
Node::Node() : state(NodeState::nsEMPTY) {}

void Node::addConnectedNode(Node *node, Axis axis, bool down)
{
    NodeConnection nc(node, axis, down);
    connectedNodes.push_back(nc);
}
std::set<Node*> Node::getConnectedNodes_Level1(bool onlyEmpty) const // = false
{
    std::set<Node*> result;
    std::ranges::transform(connectedNodes, std::inserter(result, result.begin()),
                           [onlyEmpty](const NodeConnection& nodeConnection)
                           {
                               return (!onlyEmpty || nodeConnection.node->getState() == nsEMPTY) ? nodeConnection.node : nullptr;
                           });
    result.erase(nullptr);
    return result;
}
std::set<Node*> Node::getEmptyConnectedNodes_Level2() const
{
    std::set<Node*> result;
    std::set<Node*> connectedLvl1 = getConnectedNodes_Level1();

    for(Node* node : connectedLvl1)
    {
        std::set<Node*> halfRes = node->getConnectedNodes_Level1(ONLY_EMPTY);
        result.insert(halfRes.begin(), halfRes.end());
    }

    for(Node* node : connectedLvl1)
        result.erase(node);

    result.erase(const_cast< Node* >( this ));

    return result;
}

int Node::getX() const {
    return position.getX();
}
int Node::getY() const {
    return position.getY();
}

// position
Position::Position(int x, int y) : x(x), y(y) {}

void Node::setPosition(const Position &p) {
    position = p;
}
void Node::setPosition(int x, int y) {
    this->position = Position(x, y);
}
const Position &Node::getPosition() const {
    return position;
}

int Position::getX() const {
    return x;
}
int Position::getY() const {
    return y;
}

// state
void Node::setState(NodeState s) {
    if (state != nsDISABLED)
        state = s;
}
NodeState Node::getState() const {
    return state;
}

void Node::setDisabled() {
    state = NodeState::nsDISABLED;
}
bool Node::isDisabled() const {
    return state == NodeState::nsDISABLED;
}
bool Node::isClicked(const Position& clickedPos) const
{
    return abs(clickedPos.getX() - this->getX()) <= Node::width / 4
           && abs(clickedPos.getY() - this->getY()) <= Node::height / 2;

}

NodeConnection::NodeConnection(Node* node, Axis axis, bool down)
        : node(node), axis(axis), down(down) {}

