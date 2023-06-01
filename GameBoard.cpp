//
// Created by Sonia on 23.05.2023.
//

#include <iostream>
#include "GameBoard.h"
#include <SFML/Graphics.hpp>
#include "GameBoardSerialization.h"
#include "AI.h"
#include "GameBoardDrawer.h"

const Position startingPosition = Position(400, 75);

GameBoard::GameBoard()
  : size(5), turn(PlayerTurn::turnPLAYER1), selectedNode(nullptr) {
    initBoard();
}
GameBoard::GameBoard(const GameBoard &gameBoard)
  : size(5), turn(gameBoard.getTurn()), selectedNode(nullptr) {
    initBoard();

    const std::vector< Node* >& nodesToCopy = gameBoard.getNodes();

    for (int i = 0; i < nodesToCopy.size(); ++i) {
        nodes[ i ]->setState( nodesToCopy[ i ]->getState() );
    }
}
GameBoard::~GameBoard() {
    for(Node* node : nodes)
        delete node;
}

// private
Node* GameBoard::createNode() {
    Node* node = new Node();
    this->nodes.push_back(node);
    return node;
}

void GameBoard::initBoard() {

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

//    GameBoardSerialization::deserialize(*this, "BoardState.txt");
}
void GameBoard::initSide(const std::vector<Node*>& vec, bool left ) {

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

// public

// nodes
const std::vector<Node *> &GameBoard::getNodes() const {
    return nodes;
}

void GameBoard::setSelectedNode(Node *s) {
    selectedNode = s;
}

Node *GameBoard::getSelectedNode() const {
    return selectedNode;
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

NodeState GameBoard::getNodeStateByPlayerTurn(PlayerTurn pt)
{
    return pt == turnPLAYER1 ? nsPLAYER1 : nsPLAYER2;
}
int GameBoard::getNodeQtyByNodeState(NodeState ns) const
{
    return std::count_if(nodes.begin(), nodes.end(), [ns](const Node* node) -> bool {
        return node->getState() == ns;
    });
}
std::vector<Node*> GameBoard::getNodesByNodeState(NodeState ns) const
{
    std::vector<Node*> res;
    std::copy_if(nodes.begin(), nodes.end(), std::back_inserter(res), [ns](const Node* node) -> bool {
        return node->getState() == ns;
    });
    return res;
}

int GameBoard::getNodeIndex(const Node* node) const
{
    auto it = std::find(nodes.begin(), nodes.end(), node);
    return it - nodes.begin();
}
Node* GameBoard::getNodeByIndex(const int index) const
{
    if (index >= 0 && index < nodes.size())
        return nodes[index];
    else
        return nullptr;
}

// turn
bool GameBoard::changeTurn()
{
    setSelectedNode(nullptr);
    this->turn = turn == turnPLAYER1 ? turnPLAYER2 : turnPLAYER1;

    if( !currentPlayerMoveIsPossible(turn) )
        return false;

    //
    if( playingAgainstComputer && turn == turnPLAYER2 ) {
        Node *from;
        Node *to;
        if (AI(*this).getOptimalMove(from, to)) {
            move(from, to);
            this->turn = turn == turnPLAYER1 ? turnPLAYER2 : turnPLAYER1;

            if( !currentPlayerMoveIsPossible(turn) )
                return false;
        }
    }

    return true;

//    GameBoardSerialization::serialize(*this, "BoardState.txt");
}
PlayerTurn GameBoard::getTurn() const {
    return turn;
}
PlayerTurn GameBoard::getOppositeTurn(PlayerTurn pt) { // static
    return pt == turnPLAYER1 ? turnPLAYER2 : turnPLAYER1;
}

// game state
bool GameBoard::currentPlayerMoveIsPossible(PlayerTurn pt) const
{
    const NodeState playerState = GameBoard::getNodeStateByPlayerTurn(pt);
    for(Node* node : getNodes())
    {
        if (node->getState() != playerState)
            continue;

         const std::set<Node*> nodes_Level1 = node->getConnectedNodes_Level1(ONLY_EMPTY);
         const std::set<Node*> nodes_Level2 = node->getEmptyConnectedNodes_Level2();

         if (!nodes_Level1.empty() || !nodes_Level2.empty()) {
             return true;
         }
    }
    return false;
}

// move
bool GameBoard::move(Node* nodeFrom, Node* nodeTo) const
{
    bool changeTurn = false;

    if(nodeTo->getState() == nsEMPTY )
    {
        const std::set<Node*> nodes1 = nodeFrom->getConnectedNodes_Level1(ONLY_EMPTY);
        if( nodes1.contains(nodeTo) )
        {
            nodeTo->setState(nodeFrom->getState());
            changeTurn = true;
        }

        const std::set<Node*> nodes2 = nodeFrom->getEmptyConnectedNodes_Level2();
        if( nodes2.contains(nodeTo) )
        {
            nodeTo->setState(nodeFrom->getState());
            nodeFrom->setState(nsEMPTY);
            changeTurn = true;
        }

        for(Node* node : nodeTo->getConnectedNodes_Level1())
        {
            if(node->getState() != nsEMPTY && node->getState() != nsDISABLED)
                node->setState(nodeTo->getState());
        }
    }
    return changeTurn;
}

// finish game
void GameBoard::finishGame() const
{
    //todo: set a winner, maybe make it a global variable which will be null till we get the winner,
    // not to search for it twice. Or we could keep as a winner the one who has most points and update his everytime we
    // calculate the point for each player

    if(getNodeQtyByNodeState(nsEMPTY) > 0) {

        NodeState winnerState = this->getWinnerState();
        for (Node *node: this->getNodes()) {
            if (node->getState() == nsEMPTY)
                node->setState(winnerState);
        }
    }

    std::string winner = this->getNodeQtyByNodeState(nsPLAYER1) > this->getNodeQtyByNodeState(nsPLAYER2) ?
                         "PLAYER1 WON" : "PLAYER2 WON";
    std::cout << winner;

}

NodeState GameBoard::getWinnerState() const
{
    return getNodeStateByPlayerTurn(turn == turnPLAYER1 ? turnPLAYER2 : turnPLAYER1);
}
NodeState GameBoard::getWinnerByPoints() const
{
    return this->getNodeQtyByNodeState(nsPLAYER1) > this->getNodeQtyByNodeState(nsPLAYER2) ? nsPLAYER1 : nsPLAYER2;
}

int GameBoard::getWinningPointsQty() const {
    const int playerPointQty = getNodeQtyByNodeState(GameBoard::getNodeStateByPlayerTurn(getTurn()));
    const int opponentPointQty =
            getNodeQtyByNodeState(GameBoard::getNodeStateByPlayerTurn(GameBoard::getOppositeTurn(getTurn())));

    return playerPointQty - opponentPointQty;
}

void GameBoard::setPlayingAgainstComputer(bool playingAgainstComputer) {
    GameBoard::playingAgainstComputer = playingAgainstComputer;
}

void GameBoard::setTurn(PlayerTurn turn) {
    GameBoard::turn = turn;
}

bool GameBoard::isPlayingAgainstComputer() const {
    return playingAgainstComputer;
}
