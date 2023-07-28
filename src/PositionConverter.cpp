#include "PositionConverter.h"

PositionConverter::PositionConverter(const sf::Vector2u& windowSize, const sf::Vector2f& cellSize, const int& cellsNumber)
    : m_windowSize{windowSize}, m_cellSize{cellSize}, m_cellsNumber{cellsNumber}
{
}

sf::Vector2f PositionConverter::toPixel(const sf::Vector2i& position)
{
    return {position.x * m_cellSize.x, position.y * m_cellSize.y};
}

sf::Vector2f PositionConverter::toPixelCenter(const sf::Vector2i& position)
{
    return {(position.x * m_cellSize.x) + (m_cellSize.x / 2.f), (position.y * m_cellSize.y) + (m_cellSize.y / 2.f)};
}

sf::Vector2f PositionConverter::toLightPositionInShader(const sf::Vector2i& position)
{
    return {(position.x * m_cellSize.x) + (m_cellSize.x / 2.f), m_windowSize.y - ((position.y * m_cellSize.y) + (m_cellSize.y / 2.f))};
}