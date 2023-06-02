#ifndef HEXAGON_MAIN_MENU
#define HEXAGON_MAIN_MENU

#include <SFML/Graphics.hpp>

class MainMenuShower
{
private:
    sf::Font font; /*!< The font used for menu item text. */
//  sf::Texture cellTexture;

    int hoverMenuItemIndex; /*!< The index of the menu item currently being hovered over. */
    int posY; /*!< The current vertical y-coordinate for drawing the next menu item. */
    int menuItemIndex; /*!< The index of the next menu item. */

    /**
     * @brief Draws the next menu item text on the window.
     *
     * @param window The SFML RenderWindow to draw on.
     * @param caption The text caption of the menu item.
     */
    void drawNextMenuText(sf::RenderWindow& window, const std::string& caption);

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
    int showMainMenuFrame();
};

#endif