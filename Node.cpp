//
// Created by Sonia on 23.05.2023.
//

#include "Node.h"

NodeConnection::NodeConnection(Node* node, Axis axis, bool down)
        : node(node), axis(axis), down(down) {}

Node::Node() : enabled(true) {}

void Node::addConnectedNode(Node *node, Axis axis, bool down)
{
    NodeConnection nc(node, axis, down);
    connectedNodes.push_back(nc);
}

bool Node::isEnabled() const {
    return enabled;
}

void Node::setEnabled(bool enabled) {
    Node::enabled = enabled;
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

