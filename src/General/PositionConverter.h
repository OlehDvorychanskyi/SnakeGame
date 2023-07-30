#pragma once 
#include <SFML/Graphics.hpp>

class PositionConverter
{
private: 
    sf::Vector2u m_windowSize;
    sf::Vector2f m_cellSize;
    int m_cellsNumber;
public:
    PositionConverter(const sf::Vector2u& windowSize, const sf::Vector2f& cellSize, const int& cellsNumber);

    sf::Vector2f toPixel(const sf::Vector2i& position);
    sf::Vector2f toPixelCenter(const sf::Vector2i& position);
    sf::Vector2f toLightPositionInShader(const sf::Vector2i& position);

    const int& getCellsNumber() const { return m_cellsNumber; }
    const sf::Vector2f& getCellSize() const { return m_cellSize; }

    void resize(const unsigned int& newWindowWidth, const unsigned int& newWindowHeight);
};