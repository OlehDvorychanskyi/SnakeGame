#pragma once 
#include <SFML/Graphics.hpp>

class PositionManager
{
private: 
    sf::Vector2u m_windowSize;
    sf::RenderWindow* m_window;
public:
    PositionManager(sf::RenderWindow* windowSize);

    sf::Vector2f toCenterPositionInOpenGL(const sf::Vector2f& position, const sf::Vector2f& size);
    sf::Vector2f toPositionInOpenGL(const sf::Vector2f& position);

    sf::Vector2f percentToPixel(const sf::Vector2f& positionInPercentage);
    sf::Vector2f pixelToPercent(const sf::Vector2f& positionInPixels);

    void resize(const unsigned int& newWindowWidth, const unsigned int& newWindowHeight);

    // sf::Vector2f getCellSize(const sf::Vector2i& cellsNumber);
    sf::Vector2f getCellSize(const sf::Vector2i& cellsNumber);

    sf::Vector2f getMousePosition();
};