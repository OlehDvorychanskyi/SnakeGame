#pragma once 
#include <SFML/Graphics.hpp>

class DataCell 
{
private:
    sf::Vector2i m_position;
    sf::Color m_color;
public: 
    DataCell(const int& x, const int& y, const sf::Color& color);
    DataCell(const sf::Vector2i& position, const sf::Color& color);

    void SetColor(const sf::Color& color);
    void AddColor(const sf::Color& color);
    const sf::Color& GetColor() const;

    void SetPosition(const int& x, const int& y);
    void SetPosition(const sf::Vector2i& position);
    void AddPosition(const int& x, const int& y);
    void AddPosition(const sf::Vector2i& position);
    const sf::Vector2i& GetPosition() const; 
};