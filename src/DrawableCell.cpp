#include "DrawableCell.h"

DrawableCell::DrawableCell(const sf::Vector2f& cell_size, const int& x, const int& y, const sf::Color& color)
{
    m_rectangle.setSize(cell_size);
    m_rectangle.setPosition(cell_size.x * x, cell_size.y * y);
    m_rectangle.setFillColor(color);
}

void DrawableCell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rectangle, states);
}

void DrawableCell::SetColor(const sf::Color& color)
{
    m_rectangle.setFillColor(color);
}