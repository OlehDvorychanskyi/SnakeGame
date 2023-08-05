#pragma once 
#include <SFML/Graphics.hpp>

#include "World.h"
#include "MainMenu.h"
#include "PositionManager.h"
#include "ShaderManager.h"

#include "ConfigLoader.h"


/* Things for first release:

    1. Game stages like Intro, MainMenu, Game, LoseWindow, WinWindow and so on. Also need to implement all of this stages 

    2. Separate all src by folders so that all files related to MainMenu will be in one folder called MainMenu and general files will either be in the same folder with main.cpp or in a separate folder

    3. Add music and sound to game

    4. l think fruits should be smaller than cell in my game and should be like a 2 times smaller rectangle inside cell

    5. Needs to add window resize method by specifying actuall aspect ration. Like now aspect ration is 1:1, but l also need to add 16:9 and some other common aspect rations

    6. Improve game architecture and fix all known bugs

    7. Create nice README.md file and write a paragraph about game arcitecture and why you create all of this classes

    8. Create a game intro and paste it on github

    9. Add scores to game
*/



class Game
{
    enum GameStages { Menu, InGame, ScoreMenu };
private:
    sf::Vector2i m_cells_number;
    ConfigLoader config;
    
    sf::RenderWindow* m_window;
    PositionManager* m_positionManager;
    ShaderManager* m_shaderManager;
    FontManager* m_fontManager;
    
    World* m_world;
    MainMenu* m_menu;

    int m_stage;
    
    sf::Clock clock;
    sf::Context context;

    void changeStage(const int& from, const int& to);

    void processEvents();
    void update();
    void render();
public:
    Game();
    ~Game();
    void run();
};