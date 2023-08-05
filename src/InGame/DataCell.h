#pragma once 
#include <SFML/Graphics.hpp>

class DataCell 
{
private:
    sf::Vector2i m_position;
    sf::Color m_color;
public: 
    DataCell(const int& x = 0, const int& y = 0, const sf::Color& color = sf::Color::White);
    DataCell(const sf::Vector2i& position = {0, 0}, const sf::Color& color = sf::Color::White);

    void SetColor(const sf::Color& color);
    void AddColor(const sf::Color& color);
    void SubtructColor(const sf::Color& color);
    const sf::Color& GetColor() const;

    void SetPosition(const int& x, const int& y);
    void SetPosition(const sf::Vector2i& position);
    void AddPosition(const int& x, const int& y);
    void AddPosition(const sf::Vector2i& position);
    const sf::Vector2i& GetPosition() const;
    sf::Vector2f GetFloatPosition() const;  

    bool operator==(const sf::Vector2i& position) const 
    {
        return this->m_position == position;
    }
};