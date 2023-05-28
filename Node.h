//
// Created by Sonia on 23.05.2023.
//

#ifndef PJC_NODE_H
#define PJC_NODE_H

#include <vector>
#include <set>

enum Axis{
    AXIS_1, // left
    AXIS_2, // vertical
    AXIS_3  // right
};

enum NodeState{
    nsEMPTY,
    nsPLAYER1,
    nsPLAYER2,
    nsDISABLED
};

class Node;

struct Position
{
    float x;
    float y;
    Position(float x = 0.0f, float y = 0.0f);

    float getX() const;
    float getY() const;
};

struct NodeConnection
{
    NodeConnection(Node* node1, Axis axis1, bool down1);

    Node* node;
    Axis axis;
    bool down; // going to smaller numbers on axis
};

class Node
{
private:
    NodeState state;

public:
    Node();
    std::vector<NodeConnection> connectedNodes;
    Position position;

    static const float height;
    static const float width;
    static const float margin;

    bool isDisabled() const;
    void setDisabled();

    NodeState getState() const;

    void setState(NodeState state);

    void addConnectedNode(Node* node, Axis axis, bool down);

    Node* getVerticalDownConnectedNode() const;

    const Position &getPosition() const;
    void setPosition(const Position& position);
    void setPosition(float x, float y);

    float getX() const;
    float getY() const;

    bool isClicked(const Position& clickedPos) const;

    std::set<Node*> getConnectedNodes() const;


};

#endif //PJC_NODE_H
