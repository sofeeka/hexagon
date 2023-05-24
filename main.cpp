#include <iostream>
#include "GameBoard.h"
#include <SFML/Graphics.hpp>

int main() {
    GameBoard gameBoard;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Ex_Dino");
    sf::Event event;

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
    return 0;
}
