#include "MainMenu.h"
#include <iostream>

static const int FONT_SIZE = 20;
static const int TOP_Y = 100;
static const int MARGIN_Y = 50;
static const int posX = 200;

int getSelectedMenuItemIndex( int mouseX, int mouseY )
{
  int result = ( mouseY - TOP_Y ) / ( MARGIN_Y );
  return result;
}

bool MainMenuShower::prepare()
{
  try {
    if (!font.loadFromFile("Standard_International.ttf")) {
      std::cout << "error: unable to load font file Standard_International.ttf" << "\n";
      return false;
    }
  }
  catch (...)
  {
    return false;
  }

  return true;
}

void MainMenuShower::drawNextMenuText(sf::RenderWindow& window, const std::string& caption)
{
  sf::Text text1(font, caption, FONT_SIZE);
  text1.setFillColor(hoverMenuItemIndex == menuItemIndex ? sf::Color::Green : sf::Color::Yellow);
  text1.setPosition(sf::Vector2f(posX, posY));
  posY += MARGIN_Y;
  window.draw(text1);

  menuItemIndex++;
}

int MainMenuShower::showMainMenuFrame() 
{
  sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Hexxagon game", sf::Style::Close);

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        return -1;
      }

      if (event.type == sf::Event::MouseButtonPressed)
      {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        const int clickedMenuItemIndex = getSelectedMenuItemIndex(mousePos.x, mousePos.y);

        switch (clickedMenuItemIndex)
        {
        case 0:; return 0;// run new game against computer
        case 1:; return 1;// run new game between humans
        case 2:; // load game
        case 3:; // show high score list
        }
      }

      if (event.type == sf::Event::MouseMoved)
      {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        hoverMenuItemIndex = getSelectedMenuItemIndex(mousePos.x, mousePos.y);
      }
    }

    //
    this->posY = TOP_Y;
    this->menuItemIndex = 0;

    // Draw menu items
    drawNextMenuText(window, "New game against computer");
    drawNextMenuText(window, "New game between humans");
    drawNextMenuText(window, "Load saved game");
    drawNextMenuText(window, "High score");

    //
    window.display();
  }
}
