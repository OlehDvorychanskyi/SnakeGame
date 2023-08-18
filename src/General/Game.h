#pragma once 
#include <SFML/Graphics.hpp>
#include "World.h"
#include "MainMenu.h"


/* Things for first release:

    7. Create nice README.md file and write a paragraph about game arcitecture and why you create all of this classes
*/



class Game
{
    enum GameStages { Menu, InGame, ScoreMenu };
private:
    sf::Vector2i m_cells_number;
    
    sf::RenderWindow* m_window;
    World* m_world;
    MainMenu* m_menu;

    int m_stage;
    
    sf::Clock clock;
    sf::Context context;

    void changeStage(int to);

    void processEvents();
    void update();
    void render();

    int m_speed;
public:
    Game();
    ~Game();
    void run();
};