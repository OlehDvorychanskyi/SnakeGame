#pragma once 
#include <SFML/Graphics.hpp>
#include "Cell.h"

class Fruit : public sf::Drawable
{
public:
    Cell m_body;

    Fruit(const sf::Vector2f& cell_size);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};