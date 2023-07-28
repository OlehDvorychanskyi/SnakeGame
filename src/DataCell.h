#pragma once 
#include <SFML/Graphics.hpp>

class DataCell 
{
private:
    sf::Vector2i m_position;
    sf::Color m_color;
public: 
    DataCell(const int& x, const int& y, const sf::Color& color = sf::Color::White);
    DataCell(const sf::Vector2i& position, const sf::Color& color = sf::Color::White);

    void SetColor(const sf::Color& color);
    void AddColor(const sf::Color& color);
    void SubtructColor(const sf::Color& color);
    const sf::Color& GetColor() const;

    void SetPosition(const int& x, const int& y);
    void SetPosition(const sf::Vector2i& position);
    void AddPosition(const int& x, const int& y);
    void AddPosition(const sf::Vector2i& position);
    const sf::Vector2i& GetPosition() const; 

    // const sf::Vector2f& GetWorldPosition(const sf::Vector2f& cellSize);
};