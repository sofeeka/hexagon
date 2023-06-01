//
// Created by Sonia on 02.06.2023.
//

#include <iostream>
#include "Dialog.h"
#include "SFML/Graphics.hpp"

std::string Dialog::getUserInputString(const std::string& title, const std::string& defaultText) {

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(400, 200)), title);

    sf::Font font;
    if (!font.loadFromFile("Standard_International.ttf")) {
        std::cout << "Failed to load font" << std::endl;
        return "";
    }

    std::string inputString = defaultText;

    sf::Text text(font, inputString, 24);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(10, 10));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return "";
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == 13)
                        return inputString;

                    if (event.text.unicode == '\b' && !inputString.empty())
                        inputString.pop_back();
                    else if (event.text.unicode != '\b')
                        inputString += static_cast<char>(event.text.unicode);

                    text.setString(inputString);
                }
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }

    return inputString;
}
