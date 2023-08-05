#include "PositionManager.h"

PositionManager::PositionManager(sf::RenderWindow* windowPtr)
{
    m_window = windowPtr;
    m_windowSize = m_window->getSize();
}

sf::Vector2f PositionManager::percentToPixel(const sf::Vector2f& positionInPercentage)
{
    return { m_windowSize.x * positionInPercentage.x / 100.f, m_windowSize.y * positionInPercentage.y / 100.f };
}

sf::Vector2f PositionManager::pixelToPercent(const sf::Vector2f& positionInPixels)
{
    return { positionInPixels.x * 100.f / m_windowSize.x, positionInPixels.y * 100.f / m_windowSize.y };    
}

sf::Vector2f PositionManager::toCenterPositionInOpenGL(const sf::Vector2f& position, const sf::Vector2f& size)
{
    return {(position.x * size.x) + (size.x / 2.f), m_windowSize.y - ((position.y * size.y) + (size.y / 2.f))};
}

sf::Vector2f PositionManager::toPositionInOpenGL(const sf::Vector2f& position)
{
    return {position.x, m_windowSize.y - position.y};
}

void PositionManager::resize(const unsigned int& newWindowWidth, const unsigned int& newWindowHeight)
{
    m_windowSize = sf::Vector2u(newWindowWidth, newWindowHeight);
}

// sf::Vector2f PositionManager::getCellSize(const sf::Vector2i& cellsNumber)
// {
//     return {(float)m_windowSize.x / (float)cellsNumber.x, (float)m_windowSize.y / (float)cellsNumber.y};
// }

sf::Vector2f PositionManager::getCellSize(const sf::Vector2i& cellsNumber)
{
    return {(float)m_windowSize.x / (float)cellsNumber.x, (float)m_windowSize.y / (float)cellsNumber.y};
}

sf::Vector2f PositionManager::getMousePosition()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
    return {mousePos.x, mousePos.y};
}