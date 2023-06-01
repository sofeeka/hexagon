#ifndef HEXAGON_MAIN_MENU
#define HEXAGON_MAIN_MENU

#include <SFML/Graphics.hpp>

class MainMenuShower
{
private:
  sf::Font font;
//  sf::Texture cellTexture;

  int hoverMenuItemIndex;
  int posY;
  int menuItemIndex;
  void drawNextMenuText(sf::RenderWindow& window, const std::string& caption);

public:
  bool prepare();

  int showMainMenuFrame();
};

#endif