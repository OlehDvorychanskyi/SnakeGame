#pragma once 
#include <SFML/Graphics.hpp>
#include "World.h"

class Game
{
private:
    sf::RenderWindow m_window;
    World m_world;

    void processEvents();
    void update();
    void render();
public:
    Game();
    void run();
};