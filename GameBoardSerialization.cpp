#include "GameBoardSerialization.h"
#include <iostream>
#include <fstream>
// local
/**
 * @brief Converts a NodeState enum value to a corresponding string representation.
 *
 * @param ns The NodeState value to convert.
 * @return The string representation of the NodeState value.
 */
static std::string getStringByState(NodeState ns)
{
    switch(ns)
    {
        case nsPLAYER1 :
            return "P1";
        case nsPLAYER2 :
            return "P2";
        case nsDISABLED :
            return "DISABLED";
        default:
            return "EMPTY";
    }
}

/**
 * @brief Converts a PlayerTurn enum value to a corresponding string representation.
 *
 * @param pt The PlayerTurn value to convert.
 * @return The string representation of the PlayerTurn value.
 */
static std::string getStringByTurn(PlayerTurn pt)
{
    return (pt == turnPLAYER1) ? "PLAYER1" : "PLAYER2";
}

/**
 * @brief Converts a string representation to the corresponding NodeState enum value.
 *
 * @param s The string representation to convert.
 * @return The NodeState value corresponding to the input string.
 */
static NodeState getStateByString(const std::string& s)
{
    if(s == "P1")
        return nsPLAYER1;
    if(s == "P2")
        return nsPLAYER2;
    if(s == "DISABLED" )
        return nsDISABLED;
    return nsEMPTY;
}

/**
 * @brief Converts a string representation to the corresponding PlayerTurn enum value.
 *
 * @param s The string representation to convert.
 * @return The PlayerTurn value corresponding to the input string.
 */
static PlayerTurn getTurnByString(const std::string& s)
{
    return (s == "PLAYER1") ? turnPLAYER1 : turnPLAYER2;
}

void GameBoardSerialization::serialize(const GameBoard &gameBoard, const std::string &fileName) // static
{
    std::ofstream file;
    file.open(fileName, std::ios::out );

    file << getStringByTurn(gameBoard.getTurn()) << "\n";
    std::string s = gameBoard.isPlayingAgainstComputer() ? "COMPUTER" : "HUMAN";
    file << s << "\n";

    const std::vector< Node* >& nodes = gameBoard.getNodes();

    for(Node* node : nodes)
    {
        file << getStringByState(node->getState()) << "\n";
    }

    file.close();
}

bool GameBoardSerialization::deserialize(GameBoard &gameBoard, const std::string &fileName) // static
{
    std::ifstream file;
    file.open(fileName, std::ios::in );

    std::string s;

    std::getline(file, s); // turn
    gameBoard.setTurn(getTurnByString(s));

    std::getline(file, s); // COMPUTER vs HUMAN
    gameBoard.setPlayingAgainstComputer(s == "COMPUTER");

    const std::vector< Node* >& nodes = gameBoard.getNodes();

    for(Node* node : nodes)
    {
        std::getline(file, s);
        node->setState(getStateByString(s));
    }

    file.close();

    return true;
}