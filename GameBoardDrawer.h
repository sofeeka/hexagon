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

    sf::Font font;

    bool prepared;
    bool prepare();

    static void drawNodeHexagon( sf::RenderWindow& window, const Node* node, const sf::Color& color);
    static void drawCircle(sf::RenderWindow &window, const Node *node, const sf::Color &color);
    void drawScores(sf::RenderWindow &window) const;

public:
    GameBoardDrawer(const GameBoard* gameBoard);

    bool isPrepared() const;

    void draw(sf::RenderWindow& window) const;

    void drawTurn(sf::RenderWindow &window) const;
};


#endif //HEXAGON_GAMEBOARDDRAWER_H
