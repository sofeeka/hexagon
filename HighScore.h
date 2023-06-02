#ifndef HEXAGON_HIGHSCORE_H
#define HEXAGON_HIGHSCORE_H

#include <map>
#include "SFML/Graphics.hpp"

/**
* @class MainMenuShower
* @brief Class for displaying the main menu of the game.
*/
class HighScore
{
private:
    sf::Font font; /*!< The font used for menu item text. */

    int hoverMenuItemIndex; /*!< The index of the menu item currently being hovered over. */
    int posY; /*!< The current vertical y-coordinate for drawing the next menu item. */
    int menuItemIndex; /*!< The index of the next menu item. */

    std::multimap<int, std::string> highScoreRecords; /*!<Multimap representing the high score records.*/

    /**
     * @brief Draws the next menu item text on the window.
     *
     * @param window The SFML RenderWindow to draw on.
     * @param caption The text caption of the menu item.
     */
    void drawNextText(sf::RenderWindow& window, const std::string& caption);

    /**
     * @brief Loads high score records from a file.
     * @return `true` if the records were successfully loaded, `false` otherwise.
     */
    bool loadRecordsFromFile();

    /**
     * @brief Saves high score records to a file.
     * @return `true` if the records were successfully saved, `false` otherwise.
     */
    bool saveRecordsToFile();

public:

    /**
     * @brief Prepares the main menu by loading the required font file.
     *
     * @return True if the preparation was successful, false otherwise.
     */
    bool prepare();

    /**
     * @brief Displays the main menu frame and handles user interactions.
     *
     * @return The index of the selected menu item, or -1 if the window was closed.
     */
    int showHighScoreFrame();

    /**
     * @brief Constructs a HighScore object.
     */
    HighScore();

/**
 * @brief Adds a new high score record.
 *
 * This function adds a new high score record to the multimap. The record consists of the user name and the
 * corresponding score. The record is inserted into the multimap.
 * If multiple records have the same score, they will appear in the order they were added.
 *
 * @param userName The user name associated with the high score.
 * @param score The score to be added.
 */
    void addNewRecord(const std::string& userName, int score);
};

#endif //HEXAGON_HIGHSCORE_H