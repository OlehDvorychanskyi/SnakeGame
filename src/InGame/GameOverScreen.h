#pragma once 
#include <SFML/Graphics.hpp>

class GameOverScreen : public sf::Drawable
{
private:
    sf::Text m_text;
    sf::Text m_restart;
    sf::Text m_scoresText;
    sf::RectangleShape darkBackground;
public:
    GameOverScreen(int scores);
    void setText();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};