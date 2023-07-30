#pragma once 
#include <SFML/Graphics.hpp>
#include "World.h"

#include "PositionConverter.h"

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

enum class GameStage { MainMenu, InGame };

class Game
{
private:
    int m_cells_number = 15;
    
    sf::RenderWindow m_window;
    PositionConverter m_positionConvertor;
    World m_world;

    GameStage m_stages;
    
    void processEvents();
    void update();
    void render();
public:
    Game();
    void run();
};