#pragma once 
#include <SFML/Graphics.hpp>

class Cell
{
private:
    sf::RectangleShape rectangle;
    sf::Vector2i position_xy;
public:
    Cell(const sf::Vector2f& cell_size);
    Cell(const sf::Vector2f& cell_size, const int& x, const int& y, const sf::Color& color = sf::Color::Green);

    void SetPosition(const int& x, const int& y);
    void SetPosition(const sf::Vector2f& position);

    const sf::Vector2f& GetPositionPX() const; // position in pixels 
    sf::Vector2i GetPositionXY() const; // position in (x,y)

    void AddPosition(const int& x, const int& y);

    void SetColor(const sf::Color& color);

    const sf::RectangleShape& GetRectangleShape() const;
};
    