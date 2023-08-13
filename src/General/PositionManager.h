#pragma once 
#include <SFML/Graphics.hpp>

namespace PositionManager
{
    extern sf::RenderWindow* m_window;

    void setRenderWindow(sf::RenderWindow* window);
    sf::Vector2f toCenterPositionInOpenGL(const sf::Vector2f& position, const sf::Vector2f& size);
    sf::Vector2f toPositionInOpenGL(const sf::Vector2f& position);
    sf::Vector2f percentToPixel(const sf::Vector2f& positionInPercentage);
    sf::Vector2f pixelToPercent(const sf::Vector2f& positionInPixels);
    sf::Vector2f getCellSize(const sf::Vector2i& cellsNumber);
    sf::Vector2f getMousePosition();
}