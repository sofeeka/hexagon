//
// Created by Sonia on 28.05.2023.
//

#include "GameBoardDrawer.h"
#include "GameBoard.h"

const float width = 15.f;
const float height = 10.f;

void GameBoardDrawer::draw(sf::RenderWindow& window)
{
    // Clear the window
    window.clear();

    // Draw the nodes
    for (auto& node : gameBoard->getNodes()) {
        sf::CircleShape circle(std::max(width,height), 6);
        circle.setPosition(sf::Vector2f(node->getX(), node->getY()));
        circle.setRotation(sf::degrees(90.f));
        circle.setScale(sf::Vector2f(1, width/height));
        window.draw(circle);
    }

    window.display();
}

GameBoardDrawer::GameBoardDrawer(const GameBoard* gameBoard) : gameBoard(gameBoard){}
