//
// Created by Sonia on 28.05.2023.
//

#include "GameBoardDrawer.h"
#include "GameBoard.h"

void GameBoardDrawer::draw(sf::RenderWindow& window)
{
    // Clear the window
    window.clear();

    // Draw the nodes
    for (auto& node : gameBoard->getNodes()) {

        if (!node->isEnabled())
            continue;

        sf::ConvexShape hexagon;
        hexagon.setPointCount(6);

        const float heightBy2 = Node::height / 2;
        const float widthBy4 = Node::width / 4;

        hexagon.setPoint(0, sf::Vector2f(-widthBy4, -heightBy2));
        hexagon.setPoint(1, sf::Vector2f(-2 * widthBy4, 0));
        hexagon.setPoint(2, sf::Vector2f(-widthBy4, heightBy2));
        hexagon.setPoint(3, sf::Vector2f(widthBy4, heightBy2));
        hexagon.setPoint(4, sf::Vector2f(2 * widthBy4, 0));
        hexagon.setPoint(5, sf::Vector2f(widthBy4, -heightBy2));

        hexagon.setPosition(sf::Vector2f(node->getX(), node->getY()));

        /*sf::CircleShape circle(std::max(Node::width , Node::height), 6);
        circle.setPosition(sf::Vector2f(node->getX(), node->getY()));
        circle.setRotation(sf::degrees(90.f));
        circle.setScale(sf::Vector2f(1, Node::width/Node::height));*/
        window.draw(hexagon);
    }

    window.display();
}

GameBoardDrawer::GameBoardDrawer(const GameBoard* gameBoard) : gameBoard(gameBoard){}
