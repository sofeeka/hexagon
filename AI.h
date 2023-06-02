#ifndef HEXAGON_AI_H
#define HEXAGON_AI_H

#include "GameBoard.h"

class AI {
private:
    const GameBoard& gameBoard;

public:
    AI(const GameBoard& gameBoard);

    bool getOptimalMove( Node*& from, Node*& to ) const;
};

#endif //HEXAGON_AI_H