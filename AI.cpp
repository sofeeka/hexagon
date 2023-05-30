//
// Created by Sonia on 30.05.2023.
//

#include "AI.h"

AI::AI(const GameBoard& gameBoard) : gameBoard(gameBoard)
{}

void AI::getOptimalMove( Node*& from, Node*& to ) const
{
    const std::vector<Node*> nodesFrom =
            gameBoard.getNodesByNodeState(GameBoard::getNodeStateByPlayerTurn(gameBoard.getTurn()));

    const int playerPointQty = nodesFrom.size();
    const int opponentPointQty =
            gameBoard.getNodeQtyByNodeState(GameBoard::getNodeStateByPlayerTurn(GameBoard::getOppositeTurn(gameBoard.getTurn())));


    for(Node* nodeFrom : nodesFrom)
    {


        std::set<Node*> nodesTo = nodeFrom->getConnectedNodes_Level1(ONLY_EMPTY);
        std::set<Node*> nodesToLevel2 = nodeFrom->getEmptyConnectedNodes_Level2();
        nodesTo.insert(nodesToLevel2.begin(), nodesToLevel2.end());

        for(Node* nodeTo : nodesTo)
        {
            GameBoard copyGameBoard(gameBoard);


        }
    }

}
