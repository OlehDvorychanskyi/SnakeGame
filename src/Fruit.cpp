#include "Fruit.h"

Fruit::Fruit(const sf::Vector2f& cell_size)
    : m_body{cell_size}
{
    m_body.SetColor(sf::Color::Red);
}

void Fruit::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(m_body.GetRectangleShape(), states);
}