#ifndef HEXAGON_GAMERUNNER_H
#define HEXAGON_GAMERUNNER_H

#include "GameBoard.h"

/**
 * @class GameRunner
 *
 * @brief Class responsible for running and managing the game execution.
 *
 * The GameRunner class implements the logic for running the game, including starting a new game, loading a saved game,
 * handling player input, updating the game state and rendering the game board.
 */
class GameRunner {
private:
    GameBoard gameBoard; /*!< Pointer to the associated GameBoard object. */

    /**
     * @brief Runs the game loop.
     *
     * This function runs the main game loop where player input is captured and the game state is updated and rendered.
     * It handles player clicks, moves, turn changes, and game termination.
     *
     * @return True if the game completed successfully, false otherwise.
     */
    bool runGame();
public:

    /**
     * @brief Runs a new game with the computer or human based on the flag.
     *
     * This function initializes a new game with the flag playingAgainstComputer and runs the game loop.
     *
     * @param playingAgainstComputer A bool indicating whether the game is played against a computer or a human.
     * @return True if the game completed successfully, false otherwise.
     */
    bool runNewGame(const bool playingAgainstComputer);

    /**
     * @brief Runs a loaded game from a file.
     *
     * This function prompts the user to enter a file name for a saved game state, loads the game state from the file,
     * and runs the game loop using the loaded game state.
     *
     * @return True if the game completed successfully, false otherwise.
     */
    bool runLoadedGame();
};

#endif //HEXAGON_GAMERUNNER_H