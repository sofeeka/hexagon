//
// Created by Sonia on 01.06.2023.
//

#include "GameRunner.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "GameBoardDrawer.h"
#include "GameBoard.h"
#include "GameBoardSerialization.h"

bool GameRunner::runNewGame(const bool playingAgainstComputer) {
    gameBoard.setPlayingAgainstComputer(playingAgainstComputer);
    return runGame();
}

bool GameRunner::runLoadedGame() {
    gameBoard.setPlayingAgainstComputer(false /*read from a file*/);
    GameBoardSerialization::deserialize(gameBoard, "BoardState.txt");
    return runGame();
}

bool GameRunner::runGame() {

    GameBoardDrawer gameBoardDrawer(&gameBoard);
    if( !gameBoardDrawer.isPrepared())
    {
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Hexxagon");

    bool gameCancelled = false;
    bool gameFinished = false;

    while (window.isOpen())
    {
        if (gameFinished)
            break;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameCancelled = true;
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                const sf::Vector2i clickPos = sf::Mouse::getPosition(window);
                const Position pos(clickPos.x, clickPos.y);

                Node* clickedNode = gameBoard.getNodeByPosition(pos);

                if(clickedNode != nullptr)
                {
                    Node* selectedNode = gameBoard.getSelectedNode();
                    if (selectedNode == nullptr || clickedNode->getState() == gameBoard.getNodeStateByPlayerTurn(gameBoard.getTurn()))
                    {
                        if (clickedNode->getState() == gameBoard.getNodeStateByPlayerTurn(gameBoard.getTurn()))
                            gameBoard.setSelectedNode(clickedNode);
                    }
                    else
                    {
                        if(clickedNode->getState() == nsEMPTY )
                        {
                            const bool changeTurn = gameBoard.move(selectedNode, clickedNode);

                            if(changeTurn && !gameBoard.changeTurn())
                                gameFinished = true;

                        }
                    }
                }
            }
        }
        gameBoardDrawer.draw(window);
    }

    if( gameCancelled )
        GameBoardSerialization::serialize(gameBoard, "BoardState.txt");
    else
        gameBoard.finishGame();

    return true;
}
