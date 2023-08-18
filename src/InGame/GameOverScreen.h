#pragma once 
#include <SFML/Graphics.hpp>

class GameOverScreen : public sf::Drawable
{
public:
    sf::Text m_text;
    sf::Text m_restart;
    sf::Text m_scoresText;
    sf::RectangleShape darkBackground;

    GameOverScreen();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};