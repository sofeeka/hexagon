//
// Created by Sonia on 30.05.2023.
//

#include "GameBoardSerialization.h"
#include <iostream>
#include <fstream>

static std::string getStringByState(NodeState ns)
{
    switch(ns)
    {
        case nsPLAYER1 :
            return "nsPLAYER1";
        case nsPLAYER2 :
            return "nsPLAYER2";
        case nsDISABLED :
            return "nsDISABLED";
        default:
            return "nsEMPTY";
    }
}

static NodeState getStateByString(const std::string& s)
{
    if(s == "nsPLAYER1")
        return nsPLAYER1;
    if(s == "nsPLAYER2")
        return nsPLAYER2;
    if(s == "nsDISABLED" )
        return nsDISABLED;
    return nsEMPTY;
}

void GameBoardSerialization::serialize(const GameBoard &gameBoard, const std::string &fileName)
{
    std::ofstream file;
    file.open(fileName, std::ios::out );

    const std::vector< Node* >& nodes = gameBoard.getNodes();

    for(Node* node : nodes)
    {
        file << getStringByState(node->getState()) << "\n";
    }

    file.close();
}

bool GameBoardSerialization::deserialize(GameBoard &gameBoard, const std::string &fileName) {

    std::ifstream file;
    file.open(fileName, std::ios::in );

    std::string s;

    const std::vector< Node* >& nodes = gameBoard.getNodes();

    for(Node* node : nodes)
    {
        std::getline(file, s);
        node->setState(getStateByString(s));
    }

    file.close();

    return true;
}
