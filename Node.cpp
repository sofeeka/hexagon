//
// Created by Sonia on 23.05.2023.
//

#include "Node.h"

NodeConnection::NodeConnection(Node* node, Axis axis, bool down)
    : node(node), axis(axis), down(down) {}

void Node::addConnectedNode(Node *node, Axis axis, bool down)
{
    NodeConnection nc(node, axis, down);
    connectedNodes.push_back(nc);
}

