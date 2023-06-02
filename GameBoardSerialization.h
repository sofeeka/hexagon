//
// Created by Sonia on 30.05.2023.
//

#ifndef HEXAGON_GAMEBOARDSERIALIZATION_H
#define HEXAGON_GAMEBOARDSERIALIZATION_H


#include "GameBoard.h"
/**
 * @class GameBoardSerialization
 * @brief Provides serialization and deserialization functionality for the GameBoard class.
 *
 * The GameBoardSerialization class allows serializing the state of a GameBoard object to a file and deserializing
 * the saved state to restore a GameBoard object. It provides static methods for serialization and deserialization.
 */
class GameBoardSerialization {
public :
    /**
     * @brief Serializes the GameBoard object and saves it to a file.
     *
     * The serialize function writes the current state of the GameBoard object to a file in a serialized format.
     * It saves the turn, whether the game is played against a computer or human, and the state of each node on the board.
     *
     * @param gameBoard The GameBoard object to serialize.
     * @param fileName The name of the file to which to save the serialized data.
     */
    static void serialize(const GameBoard& gameBoard, const std::string& fileName);

    /**
     * @brief Deserializes a GameBoard object from a file.
     *
     * The deserialize function reads the serialized data from a file and populates the GameBoard object with the saved state.
     * It retrieves the turn, whether the game is played against a computer or human, and the state of each node of the board.
     *
     * @param gameBoard The GameBoard object to populate with the deserialized data.
     * @param fileName The name of the file containing the serialized data.
     * @return True if deserialization is successful, false otherwise.
     */
    static bool deserialize(GameBoard& gameBoard, const std::string& fileName);
};

#endif //HEXAGON_GAMEBOARDSERIALIZATION_H