#pragma once 
#include <SFML/Graphics.hpp>
#include "Snake.h"

class Game
{
private:
    sf::RenderWindow m_window;
    Snake m_snake;

    void processEvents();
    void update();
    void render();
public:
    Game();
    void run();
};