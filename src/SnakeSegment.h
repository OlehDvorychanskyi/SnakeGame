#pragma once 
#include <SFML/Graphics.hpp>

class SnakeSegment
{
private:
    sf::RectangleShape rectangle;
public:
    SnakeSegment(const sf::Vector2f& rectangle_size);
    SnakeSegment(const sf::Vector2f& rectangle_size, const int& x, const int& y);

    void SetPosition(const int& x = 0, const int& y = 0);
    void SetPosition(const sf::Vector2f& position);
    void AddPosition(const int& x = 0, const int& y = 0);
    const sf::Vector2f& GetPosition(); 

    void SetColor(const sf::Color& color);

    const sf::RectangleShape& GetRectangleShape() const;
};
    