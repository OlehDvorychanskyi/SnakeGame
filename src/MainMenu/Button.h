#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
private:
    sf::RectangleShape m_button;
    sf::Shader* m_shader;
    sf::Text m_text;
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, sf::Shader* buttonShader, sf::Font* font, const std::string buttonTitle);
    Button() = default; // to use std::map
    bool isInside(const sf::Vector2f& position) const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};