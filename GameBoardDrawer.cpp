#include <iostream>
#include "GameBoardDrawer.h"
#include "GameBoard.h"

static const std::string FONT_NAME = "font.otf";

static const int margin = 30; /**< Static field standing for the distance from the sides of the window. */
static const int height = 100; /**< Static field standing for the height of the highscores rectangle. */
static const int width = 65; /**< Static field standing for the width of the highscores rectangle. */

// local

/**
 * @brief Returns the color corresponding to the specified NodeState.
 *
 * This static function returns the color that corresponds to the specified NodeState.
 * If the NodeState is nsPLAYER1, it returns sf::Color::Green.
 * If the NodeState is nsPLAYER2, it returns sf::Color::Red.
 *
 * @param ns NodeState representing the player's turn.
 * @return Color corresponding to the specified NodeState.
 */
static sf::Color getColorByTurn(NodeState ns)
{
    return ns == nsPLAYER1 ? sf::Color::Green : sf::Color::Red;
}

// constructor
GameBoardDrawer::GameBoardDrawer(const GameBoard* gameBoard) : gameBoard(gameBoard)
{
    prepared = prepare();
}

// private
void GameBoardDrawer::drawNodeHexagon( sf::RenderWindow& window, const Node* node, const sf::Color& color) const
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

    hexagon.setTexture(&cellTexture);
    hexagon.setOutlineColor(color);
    hexagon.setOutlineThickness( Node::margin );
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
void GameBoardDrawer::drawScores( sf::RenderWindow& window) const
{

    sf::ConvexShape rect;
    rect.setPointCount(4);

    static const int rlcX = 800 - margin; // right lower corner
    static const int rlcY = 600 - margin;

    rect.setPoint(0, sf::Vector2f(rlcX, rlcY));
    rect.setPoint(1, sf::Vector2f(rlcX, rlcY - height));
    rect.setPoint(2, sf::Vector2f(rlcX - width, rlcY - height));
    rect.setPoint(3, sf::Vector2f(rlcX - width, rlcY));

    rect.setFillColor(sf::Color::White);
    window.draw(rect);

    const int score1 = gameBoard->getNodeQtyByNodeState(nsPLAYER1);
    const int score2 = gameBoard->getNodeQtyByNodeState(nsPLAYER2);

    const std::string s1 = std::to_string(score1);
    const std::string s2 = std::to_string(score2);

    static const int fontSize = 30;
    static const int fontMargin = ( height - 2 * fontSize )  / 3;

    sf::Text text1(font, s1, fontSize);
    sf::Text text2(font, s2, fontSize);

    text1.setFillColor(sf::Color::Green);
    text2.setFillColor(sf::Color::Red);

    text1.setPosition(sf::Vector2f(rlcX - width + fontMargin, rlcY - height + fontMargin));
    text2.setPosition(sf::Vector2f(rlcX - width + fontMargin, rlcY - fontMargin - fontSize));

    window.draw(text1);
    window.draw(text2);
}
void GameBoardDrawer::drawTurn( sf::RenderWindow& window ) const
{
    static const float radius = std::min(Node::width , Node::height)/3;

    static const int rlcX = 800 - margin - width; // right lower corner
    static const int rlcY = 600 - margin;

    static const int fontSize = 30;
    static const int circleMargin = (height - 4 * radius ) / 3;

    sf::CircleShape circle(radius, 6);
    circle.setRotation(sf::degrees(90.f));

    if(gameBoard->getTurn() == turnPLAYER1)
        circle.setPosition(sf::Vector2f( rlcX - circleMargin, rlcY - height + circleMargin ));
    else
        circle.setPosition(sf::Vector2f( rlcX - circleMargin, rlcY - circleMargin - 2 * radius ));

    circle.setFillColor(getColorByTurn(GameBoard::getNodeStateByPlayerTurn(gameBoard->getTurn())));
    window.draw(circle);
}

// public
bool GameBoardDrawer::prepare()
{
    try {
        if (!font.loadFromFile("font.otf")){
            std::cout << "error: unable to load font file font.otf" << "\n";
            return false;
        }
        if (!cellTexture.loadFromFile("cell.jpg")){
            std::cout << "error: unable to load cell texture file cell.jpg" << "\n";
            return false;
        }

    }
    catch(...)
    {
        return false;
    }

    return true;
}
bool GameBoardDrawer::isPrepared() const {
    return prepared;
}

void GameBoardDrawer::draw(sf::RenderWindow& window) const
{
    // Clear the window
    window.clear();

    // Draw the nodes
    for (auto& node : gameBoard->getNodes()) {

        drawNodeHexagon(window, node, sf::Color::Black);

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
            case NodeState::nsPLAYER2 :
                drawCircle(window, node, getColorByTurn(node->getState()));
                break;
        }

        drawScores(window);
        drawTurn(window);
    }

    window.display();
}