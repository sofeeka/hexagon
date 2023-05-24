//
// Created by Sonia on 23.05.2023.
//

#ifndef PJC_NODE_H
#define PJC_NODE_H

#include <vector>

enum Axis{
    AXIS_1, // left
    AXIS_2, // vertical
    AXIS_3  // right
};

class Node;

struct NodeConnection
{
    NodeConnection(Node* node1, Axis axis1, bool down1);

    Node* node;
    Axis axis;
    bool down; // going to smaller numbers on axis
};


class Node
{
public:
    std::vector<NodeConnection> connectedNodes;

    void addConnectedNode(Node* node, Axis axis, bool down);
};


#endif //PJC_NODE_H
