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

static const bool ONLY_EMPTY = true;

class Node;

struct Position
{
    int x;
    int y;
    Position(int x = 0, int y = 0);

    int getX() const;
    int getY() const;
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

    static const int height;
    static const int width;
    static const int margin;

    // node
    void addConnectedNode(Node* node, Axis axis, bool down);
    std::set<Node*> getConnectedNodes_Level1(bool onlyEmpty = false) const;
    std::set<Node *> getEmptyConnectedNodes_Level2() const;

    // position
    const Position &getPosition() const;
    void setPosition(const Position& p);
    void setPosition(int x, int y);

    int getX() const;
    int getY() const;

    // state
    void setState(NodeState s);
    NodeState getState() const;

    void setDisabled();
    bool isDisabled() const;
    bool isClicked(const Position& clickedPos) const;
};

#endif //PJC_NODE_H
