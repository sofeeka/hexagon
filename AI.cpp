//
// Created by Sonia on 30.05.2023.
//

#include "AI.h"

AI::AI(const GameBoard& gameBoard) : gameBoard(gameBoard)
{}

bool AI::getOptimalMove( Node*& from, Node*& to ) const
{
    const std::vector<Node*> nodesFrom =
            gameBoard.getNodesByNodeState(GameBoard::getNodeStateByPlayerTurn(gameBoard.getTurn()));

    int winningPointQty = gameBoard.getWinningPointsQty();

    from = nullptr;
    to = nullptr;

    for(Node* nodeFrom : nodesFrom)
    {
        const int indexFrom = gameBoard.getNodeIndex(nodeFrom);

        std::set<Node*> nodesTo = nodeFrom->getConnectedNodes_Level1(ONLY_EMPTY);
        std::set<Node*> nodesToLevel2 = nodeFrom->getEmptyConnectedNodes_Level2();
        nodesTo.insert(nodesToLevel2.begin(), nodesToLevel2.end());

        for(Node* nodeTo : nodesTo)
        {
            const int indexTo = gameBoard.getNodeIndex(nodeTo);

            GameBoard copyGameBoard(gameBoard);
            Node* copyNodeFrom = copyGameBoard.getNodeByIndex(indexFrom);
            Node* copyNodeTo = copyGameBoard.getNodeByIndex(indexTo);

            copyGameBoard.move(copyNodeFrom, copyNodeTo);

            const int winningPointQtyCopy = copyGameBoard.getWinningPointsQty();

            if(winningPointQtyCopy > winningPointQty || from == nullptr)
            {
                winningPointQty = winningPointQtyCopy;
                from = nodeFrom;
                to = nodeTo;
            }

        }
    }

    return from != nullptr;
}

