#ifndef HEXAGON_GAMEBOARDDRAWER_H
#define HEXAGON_GAMEBOARDDRAWER_H

#include <SFML/Graphics.hpp>
#include "GameBoard.h"
#include "Node.h"

/**
 * @class GameBoardDrawer
 * @brief The GameBoardDrawer class is responsible for drawing the game board on the screen.
 *
 * It uses SFML library to draw the game board nodes and other graphical elements.
 * The GameBoardDrawer class is associated with a GameBoard object and provides methods to draw the nodes,
 * scores, and current turn on the screen.
 */
class GameBoardDrawer {
private:
    const GameBoard* gameBoard; /*!< Pointer to the associated GameBoard object. */

    sf::Font font; /*!< Font used for displaying text. */
    sf::Texture cellTexture; /*!< Texture used for the cell hexagons. */

    bool prepared; /*!< Flag indicating if the GameBoardDrawer is prepared for drawing. */

    /**
     * @brief Prepares the GameBoardDrawer for drawing.
     *
     * This method loads the necessary font and cell texture from files.
     * If the loading is successful, the prepared flag is set to true.
     *
     * @return True if the preparation is successful, false otherwise.
     */
    bool prepare();

    /**
     * @brief Draws a hexagon for the specified node on the SFML window with the given color.
     *
     * This method draws a hexagon shape representing the specified node on the SFML window.
     * The hexagon is positioned based on the node's coordinates, and its color is set to the specified color.
     * If the node is disabled, no hexagon is drawn.

     * @param window Reference to the SFML RenderWindow to draw on.
     * @param node Pointer to the Node object to draw the hexagon for.
     * @param color Color of the hexagon.
     */
    void drawNodeHexagon(sf::RenderWindow& window, const Node* node, const sf::Color& color) const;

    /**
     * @brief Draws a circle shape for the specified node on the SFML window with the given color.
     *
     * This static method draws a circle shape representing the specified node on the SFML window.
     * The circle is positioned based on the node's coordinates, and its color is set to the specified color.
     *
     * @param window Reference to the SFML RenderWindow to draw on.
     * @param node Pointer to the Node object to draw the circle for.
     * @param color Color of the circle.
     */
    static void drawCircle(sf::RenderWindow& window, const Node* node, const sf::Color& color);

    /**
     * @brief Draws the scores on the SFML window.
     *
     * This method draws the scores of both players on the SFML window.
     * The scores are displayed in a rectangular shape at the right lower corner of the window.
     * The score of Player 1 is shown in green, and the score of Player 2 is shown in red.
     *
     * @param window Reference to the SFML RenderWindow to draw on.
     */
    void drawScores(sf::RenderWindow& window) const;

    /**
     * @brief Draws the current turn indicator on the SFML window.
     * @param window Reference to the SFML RenderWindow to draw on.
     *
     * This method draws the current turn indicator on the SFML window.
     * The indicator is displayed as a colored circle next to the scores.
     * The color of the circle corresponds to the turn of the current player.
     */
    void drawTurn(sf::RenderWindow& window) const;

public:
    /**
     * @brief Constructor for a GameBoardDrawer object with the specified GameBoard.
     *
     * This constructor initializes a GameBoardDrawer object with the specified GameBoard.
     * The GameBoard object represents the game board that will be drawn by the drawer.
     *
     * @param gameBoard Pointer to the GameBoard object to be associated with the drawer.
     */
    GameBoardDrawer(const GameBoard* gameBoard);

    /**
     * @brief Checks if the GameBoardDrawer is prepared for drawing.
     * @return True if the GameBoardDrawer is prepared, false otherwise.
     */
    bool isPrepared() const;

    /**
     * @brief Draws the game board on the specified SFML window.
     *
     * This method clears the window, then draws the nodes, scores, and current turn on the screen.
     * The nodes are drawn as hexagons with different colors based on their state.
     * The scores are displayed in a rectangular shape at the right lower corner of the window.
     * The current turn is displayed as a colored circle next to the scores.
     * After drawing, the window is displayed.
     *
     * @param window Reference to the SFML RenderWindow to draw on.
     */
    void draw(sf::RenderWindow& window) const;
};

#endif //HEXAGON_GAMEBOARDDRAWER_H