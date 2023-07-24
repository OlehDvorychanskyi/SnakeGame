#include "Cell.h"

Cell::Cell(const sf::Vector2f& cell_size)
{
    this->rectangle.setSize(cell_size);
}

Cell::Cell(const sf::Vector2f& cell_size, const int& x, const int& y, const sf::Color& color)
{
    rectangle.setSize(cell_size);
    SetPosition(x, y);
    SetColor(color);
}

void Cell::SetPosition(const int& x, const int& y)
{
    rectangle.setPosition(rectangle.getSize().x * x, rectangle.getSize().y * y);
}

void Cell::SetPosition(const sf::Vector2f& position)
{
    rectangle.setPosition(position);
}

void Cell::AddPosition(const int& x, const int& y)
{
    rectangle.setPosition(rectangle.getPosition().x + (rectangle.getSize().x * x), rectangle.getPosition().y + (rectangle.getSize().y * y));
}

const sf::Vector2f& Cell::GetPositionPX() const 
{
    return rectangle.getPosition();
}

sf::Vector2i Cell::GetPositionXY() const
{
    return sf::Vector2i(rectangle.getPosition().x / rectangle.getSize().x, rectangle.getPosition().y / rectangle.getSize().y);
}
void Cell::SetColor(const sf::Color& color)
{
    rectangle.setFillColor(color);
}

const sf::RectangleShape& Cell::GetRectangleShape() const
{
    return rectangle;
}