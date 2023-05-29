#include <iostream>
#include <vector>
#include "GameBoard.h"
#include "GameBoardDrawer.h"
#include <SFML/Graphics.hpp>

int main() {
    GameBoard gameBoard;
    GameBoardDrawer gameBoardDrawer(&gameBoard);

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Hexxagon");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
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
                            const std::set<Node*> nodes1 = selectedNode->getConnectedNodes_Level1(ONLY_EMPTY);
                            if( nodes1.contains(clickedNode) )
                            {
                                clickedNode->setState(selectedNode->getState());
                                gameBoard.changeTurn();
                            }

                            const std::set<Node*> nodes2 = selectedNode->getEmptyConnectedNodes_Level2();
                            if( nodes2.contains(clickedNode) )
                            {
                                clickedNode->setState(selectedNode->getState());
                                selectedNode->setState(nsEMPTY);
                                gameBoard.changeTurn();
                            }

                            for(Node* node : clickedNode->getConnectedNodes_Level1())
                            {
                                if(node->getState() != nsEMPTY && node->getState() != nsDISABLED)
                                    node->setState(clickedNode->getState());
                            }

                        }
                    }

/*
                    NodeState ns1 = gameBoard.getTurn() == turnPLAYER1 ? nsPLAYER1 : nsPLAYER2;
                    NodeState ns2 = ns1 == nsPLAYER1 ? nsPLAYER2 : nsPLAYER1;

                    const std::set<Node*> nodes1 = clickedNode->getConnectedNodes_Level1();
                    const std::set<Node*> nodes2 = clickedNode->getEmptyConnectedNodes_Level2();

                    for(Node* node : nodes1)
                    {
                        node->setState(ns1);
                    }

                    for(Node* node : nodes2)
                    {
                        node->setState(ns2);
                    }

                    clickedNode->setState(ns1);
                    gameBoard.changeTurn();
*/
                }

            }
        }

        gameBoardDrawer.draw(window);
    }

    return 0;
}
