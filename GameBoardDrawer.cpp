//
// Created by Sonia on 28.05.2023.
//

#include "GameBoardDrawer.h"
#include "GameBoard.h"

void GameBoardDrawer::drawNodeHexagon( sf::RenderWindow& window, const Node* node, const sf::Color& color)
{
    if (node->isDisabled())
        return;

    sf::ConvexShape hexagon;
    hexagon.setPointCount(6);

    const float heightBy2 = Node::height / 2.0f;
    const float widthBy4 = Node::width / 4.0f;

    hexagon.setPoint(0, sf::Vector2f(-widthBy4, -heightBy2));
    hexagon.setPoint(1, sf::Vector2f(-2 * widthBy4, 0));
    hexagon.setPoint(2, sf::Vector2f(-widthBy4, heightBy2));
    hexagon.setPoint(3, sf::Vector2f(widthBy4, heightBy2));
    hexagon.setPoint(4, sf::Vector2f(2 * widthBy4, 0));
    hexagon.setPoint(5, sf::Vector2f(widthBy4, -heightBy2));

    hexagon.setPosition(sf::Vector2f(node->getX(), node->getY()));
    hexagon.setFillColor(color);

    window.draw(hexagon);
}

void GameBoardDrawer::drawCircle( sf::RenderWindow& window, const Node* node, const sf::Color& color)
{
    float radius = std::min(Node::width , Node::height)/3;

    sf::CircleShape circle(radius, 6);
    circle.setRotation(sf::degrees(90.f));
    circle.setPosition(sf::Vector2f(node->getX() + radius, node->getY() - radius));

    circle.setFillColor(color);
    window.draw(circle);

}

void GameBoardDrawer::drawScores( sf::RenderWindow& window)
{

    sf::ConvexShape rect;
    rect.setPointCount(4);

    int margin = 30;
    int height = 100;
    int width = 50;

    int rlcX = 800 - margin; // right lower corner ?
    int rlcY = 600 - margin;

    rect.setPoint(0, sf::Vector2f(rlcX, rlcY));
    rect.setPoint(1, sf::Vector2f(rlcX, rlcY - height));
    rect.setPoint(2, sf::Vector2f(rlcX - width, rlcY - height));
    rect.setPoint(3, sf::Vector2f(rlcX - width, rlcY));

    rect.setFillColor(sf::Color::White);
    window.draw(rect);

    std::string s1 = std::to_string(gameBoard->getNodeQtyByNodeState(nsPLAYER1));
    std::string s2 = std::to_string(gameBoard->getNodeQtyByNodeState(nsPLAYER2));

    sf::Font font;
    if(!font.loadFromFile("C:\\Users\\Sonia\\CLionProjects\\hexagon\\Standard_International.ttf"))
    {}

    int fontSize = 30;
    int fontMargin = ( height - 2 * fontSize )  / 3;

    sf::Text score1(font,s1, fontSize);
    sf::Text score2(font, s2, fontSize);

    score1.setFillColor(sf::Color::Black);
    score2.setFillColor(sf::Color::Black);

    score1.setPosition(sf::Vector2f(rlcX - width + fontMargin, rlcY - height + fontMargin));
    score2.setPosition(sf::Vector2f(rlcX - width + fontMargin, rlcY - fontMargin - fontSize));

    window.draw(score1);
    window.draw(score2);
}

void GameBoardDrawer::draw(sf::RenderWindow& window)
{
    // Clear the window
    window.clear();

    // Draw the nodes
    for (auto& node : gameBoard->getNodes()) {

        drawNodeHexagon(window, node, sf::Color::White);

        Node* selectedNode = gameBoard->getSelectedNode();

        if(selectedNode != nullptr)
        {
            const std::set<Node*> nodes1 = selectedNode->getConnectedNodes_Level1(ONLY_EMPTY);
            const std::set<Node*> nodes2 = selectedNode->getEmptyConnectedNodes_Level2();

            for(Node* n1 : nodes1)
            {
                drawNodeHexagon(window, n1, sf::Color::Green);
            }

            for(Node* n2 : nodes2)
            {
                drawNodeHexagon(window, n2, sf::Color::Yellow);
            }

        }

        switch ( node->getState() )
        {
            case NodeState::nsPLAYER1 :
                drawCircle(window, node, sf::Color::Green);
                break;
            case NodeState::nsPLAYER2 :
                drawCircle(window, node, sf::Color::Red);
                break;
        }

        drawScores(window);

    }

    window.display();
}

GameBoardDrawer::GameBoardDrawer(const GameBoard* gameBoard) : gameBoard(gameBoard){}
