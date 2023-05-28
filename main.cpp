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

                if(node != nullptr)
                    node->setState(node->getState() == nsPLAYER1 ? nsPLAYER2 : nsPLAYER1 );
            }
        }

        gameBoardDrawer.draw(window);
    }

/*
    sf::CircleShape dino(30, 6);
    dino.setPosition({50, 500 - dino.getRadius() * 2});

    sf::RectangleShape cacti({20, 100});
    cacti.setPosition({800, 500 - cacti.getSize().y});

    while (window.isOpen()) {
        window.clear();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        window.draw(dino);
        window.draw(cacti);

        window.display();
    }
*/
    return 0;
}
