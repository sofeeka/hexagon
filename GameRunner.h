//
// Created by Sonia on 01.06.2023.
//

#ifndef HEXAGON_GAMERUNNER_H
#define HEXAGON_GAMERUNNER_H


#include "GameBoard.h"

class GameRunner {
private:
    GameBoard gameBoard;
    bool runGame();
public:
    bool runNewGame(const bool playingAgainstComputer);

    bool runLoadedGame();
};


#endif //HEXAGON_GAMERUNNER_H
