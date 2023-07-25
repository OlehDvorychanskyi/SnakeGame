#pragma once 
#include <SFML/Graphics.hpp>

class DrawableCell : public sf::Drawable
{
private:
    sf::RectangleShape m_rectangle;
public:
    DrawableCell(const sf::Vector2f& cell_size, const int& x = 0, const int& y = 0, const sf::Color& color = sf::Color::Green);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void SetColor(const sf::Color& color);
};

