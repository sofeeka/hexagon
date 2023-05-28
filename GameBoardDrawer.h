//
// Created by Sonia on 28.05.2023.
//

#ifndef HEXAGON_GAMEBOARDDRAWER_H
#define HEXAGON_GAMEBOARDDRAWER_H

#include <SFML/Graphics.hpp>
#include "GameBoard.h"
#include "Node.h"

class GameBoardDrawer {
private:
    const GameBoard* gameBoard;
    static void drawNodeHexagon( sf::RenderWindow& window, const Node* node, const sf::Color& color);
    static void drawCircle(sf::RenderWindow &window, const Node *node, const sf::Color &color);

public:
    GameBoardDrawer(const GameBoard* gameBoard);
    void draw(sf::RenderWindow& window);

};


#endif //HEXAGON_GAMEBOARDDRAWER_H
