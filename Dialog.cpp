//
// Created by Sonia on 02.06.2023.
//

#include <iostream>
#include "Dialog.h"
#include "SFML/Graphics.hpp"

static const int DIALOG_HEIGHT = 200;
static const int DIALOG_WIDTH = 400;

std::string Dialog::getUserInputString(const std::string& title, const std::string& defaultText) {

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(DIALOG_WIDTH, DIALOG_HEIGHT)), title);

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
                    if (event.text.unicode == 13) // enter
                        return inputString;

                    if (event.text.unicode == 27) // escape
                        return inputString;

                    if (event.text.unicode == '\b' && !inputString.empty()) // backspace
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
bool Dialog::showMessageDialog(const std::string& msg)
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u (DIALOG_WIDTH, DIALOG_HEIGHT)), "Message Box");

    // Create message box components
    sf::RectangleShape box(sf::Vector2f(300, 150));
    box.setFillColor(sf::Color::White);
    box.setPosition(sf::Vector2f(50, 25));

    sf::Font font;
    if (!font.loadFromFile("Standard_International.ttf"))
    {
        return false;
    }

    sf::Text message(font,msg, 24);
    message.setPosition(sf::Vector2f (70, 65));
    message.setFillColor(sf::Color::Black);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(box);
        window.draw(message);
        window.display();
    }
    return true;
}