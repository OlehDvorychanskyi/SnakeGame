#pragma once 
#include <SFML/Graphics.hpp>

class Game
{
private:
    sf::RenderWindow m_window;

    void processEvents();
    void update();
    void render();
public:
    Game();
    void run();
};