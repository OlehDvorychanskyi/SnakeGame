#pragma once 
#include <SFML/Graphics.hpp>
#include "World.h"

#include "PositionConverter.h"

class Game
{
private:
    int m_cells_number = 15;
    
    sf::RenderWindow m_window;
    PositionConverter m_positionConvertor;
    World m_world;


    void processEvents();
    void update();
    void render();
public:
    Game();
    void run();
};