//
// Created by Sonia on 30.05.2023.
//

#ifndef HEXAGON_GAMEBOARDSERIALIZATION_H
#define HEXAGON_GAMEBOARDSERIALIZATION_H


#include "GameBoard.h"

class GameBoardSerialization {
public :
    static void serialize(const GameBoard& gameBoard, const std::string& fileName);
    static bool deserialize(GameBoard& gameBoard, const std::string& fileName);
};


#endif //HEXAGON_GAMEBOARDSERIALIZATION_H
