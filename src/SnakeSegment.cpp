#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(const sf::Vector2f& rectangle_size)
{
    this->rectangle.setSize(rectangle_size);
}

SnakeSegment::SnakeSegment(const sf::Vector2f& rectangle_size, const int& x, const int& y)
{
    rectangle.setSize(rectangle_size);
    SetPosition(x, y);
}

void SnakeSegment::SetPosition(const int& x, const int& y)
{
    rectangle.setPosition(rectangle.getSize().x * x, rectangle.getSize().y * y);
}

void SnakeSegment::SetPosition(const sf::Vector2f& position)
{
    rectangle.setPosition(position);
}

void SnakeSegment::AddPosition(const int& x, const int& y)
{
    rectangle.setPosition(rectangle.getPosition().x + (rectangle.getSize().x * x), rectangle.getPosition().y + (rectangle.getSize().y * y));
}

const sf::Vector2f& SnakeSegment::GetPosition()
{
    return rectangle.getPosition();
}

void SnakeSegment::SetColor(const sf::Color& color)
{
    rectangle.setFillColor(color);
}

const sf::RectangleShape& SnakeSegment::GetRectangleShape() const
{
    return rectangle;
}