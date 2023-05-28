#include <iostream>
#include <vector>
#include "GameBoard.h"
#include "GameBoardDrawer.h"
#include <SFML/Graphics.hpp>

const sf::Color defaultColor = sf::Color::White;
const sf::Color disabledColor = sf::Color::Black;
const sf::Color highlightColor = sf::Color::Yellow;

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

                Node* node = gameBoard.getNodeByPosition(pos);

                if(node != nullptr && node->getState() == nsEMPTY)
                {
                    NodeState ns = gameBoard.getTurn() == turnPLAYER1 ? nsPLAYER1 : nsPLAYER2;

                    const std::set<Node*> nodes = node->getConnectedNodes();
                    for(Node* node : nodes)
                    {
                        node->setState(ns);
                    }

                    node->setState(ns);
                    gameBoard.changeTurn();
                }

            }
        }

        gameBoardDrawer.draw(window);
    }

    return 0;
}
