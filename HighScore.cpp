#include <iostream>
#include <fstream>
#include "HighScore.h"

static const int FONT_SIZE = 24; /*!< Font size for the text in main menu. */
static const int TOP_Y = 100; /*!< First top margin. */
static const int MARGIN_Y = 50; /*!< Margin per text line. */
static const int posX = 130; /*! X-coordinate position of the text. */
static const std::string HIGHSCORE_FILENAME = "HighScore.txt";

HighScore::HighScore()
{
    loadRecordsFromFile();
}

static int getSelectedMenuItemIndex( int mouseX, int mouseY )
{
    int result = ( mouseY - TOP_Y ) / ( MARGIN_Y );
    return result;
}

bool HighScore::prepare()
{
    try {
        if (!font.loadFromFile("font.otf")) {
            std::cout << "error: unable to load font file font.otf" << "\n";
            return false;
        }

    }
    catch (...)
    {
        return false;
    }

    return true;
}

void HighScore::drawNextText(sf::RenderWindow& window, const std::string& caption)
{
    sf::Text text1(font, caption, FONT_SIZE);
    text1.setFillColor(hoverMenuItemIndex == menuItemIndex ? sf::Color::Green : sf::Color::Yellow);
    text1.setPosition(sf::Vector2f(posX, posY));
    posY += MARGIN_Y;
    window.draw(text1);

    menuItemIndex++;
}

int HighScore::showHighScoreFrame()
{
    prepare();

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "HighScores", sf::Style::Close);

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

                if(clickedMenuItemIndex >= 0)
                    return clickedMenuItemIndex;
            }

            if (event.type == sf::Event::MouseMoved)
            {
                const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                hoverMenuItemIndex = getSelectedMenuItemIndex(mousePos.x, mousePos.y);
            }
        }

        this->posY = TOP_Y;
        this->menuItemIndex = 0;

        int qty = 0;
        for(auto rec = highScoreRecords.rbegin(); rec != highScoreRecords.rend(); ++rec, ++qty)
        {
            if(qty >= 5)
                break;
            std::string s = rec->second + " -> " + std::to_string(rec->first);
            drawNextText(window, s);
        }

        window.display();
    }
    return -1;
}

bool HighScore::loadRecordsFromFile()
{
    std::ifstream file;
    file.open(HIGHSCORE_FILENAME, std::ios::in );

    if(!file.is_open())
        return false;

    while(!file.eof()) // end of file
    {
        std::string userName;
        std::getline(file, userName);

        std::string score;
        std::getline(file, score);

        if(userName.empty() || score.empty())
            continue;

        highScoreRecords.insert(std::pair(stoi(score),userName ));
    }
    return true;
}

bool HighScore::saveRecordsToFile()
{
    std::ofstream file;
    file.open(HIGHSCORE_FILENAME, std::ios::out );

    int qty = 0;

    for(auto rec = highScoreRecords.rbegin(); rec != highScoreRecords.rend(); ++rec, ++qty) // reverse iterator
    {
        if(qty >= 5)
            break;

        file << rec->second << "\n";
        file << rec->first << "\n";
    }

    file.close();
    return true;
}

void HighScore::addNewRecord(const std::string& userName, int score)
{
    highScoreRecords.insert(std::pair(score,userName));
    saveRecordsToFile();
}