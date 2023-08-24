#include "Game.h"
#include <iostream>

#include <NumberGenerator.h>
#include <PositionManager.h>
#include <ResourceHolder.h>
#include <ConfigLoader.h>

Game::Game()
{
    unsigned width = ConfigLoader::Config->get("Window", "width", 800U);
    unsigned height = ConfigLoader::Config->get<unsigned>("Window", "height", 800U);

    if (ConfigLoader::Config->get<bool>("Window", "fullscreen", false) == false)
        m_window = new sf::RenderWindow(sf::VideoMode(width, height), "Snake");
    else    
        m_window = new sf::RenderWindow(sf::VideoMode(width, height), "Snake", sf::Style::Fullscreen);

    PositionManager::setRenderWindow(m_window);
    
    int WidthCells = ConfigLoader::Config->get<int>("World", "widthCells", 10);
    int HeightCells = ConfigLoader::Config->get<int>("World", "heightCells", 10);
    m_cells_number = {WidthCells, HeightCells};

    m_speed = ConfigLoader::Config->get<int>("Snake", "speed", 10);

    m_stage = GameStages::Menu;
    m_menu = new MainMenu();
    m_window->setMouseCursorVisible(true);
}

void Game::run()
{
    while (m_window->isOpen() == true)
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Resized)
        {
            // Maybe create a window class and add this resize functionality into it
            sf::View newView({(float)event.size.width / 2.f, (float)event.size.height / 2.f}, {(float)event.size.width, (float)event.size.height});
            m_window->setView(newView);

            // m_positionManager->resize(event.size.width, event.size.height);

            // if (m_stage == GameStages::InGame)
            // {
            //     delete m_world;
            //     m_world = new World(m_shaderManager, m_cells_number, m_fontManager);
            // } 
            // else if (m_stage == GameStages::Menu)
            // {
            //     delete m_menu;
            //     m_menu = new MainMenu(m_shaderManager, m_fontManager);
            // }
        }

        if (event.type == sf::Event::Closed)
            m_window->close();

        switch (m_stage)
        {
            case GameStages::Menu:
                m_menu->processInput(event);
                if (m_menu->isButtonPressed("Start")) 
                    changeStage(GameStages::InGame);
                else if (m_menu->isButtonPressed("Exit"))
                    m_window->close();
                break;
            case GameStages::InGame:
                if (event.type == sf::Event::KeyPressed)
                {
                    m_world->processInput(event.key.code);
                }

                if (event.key.code == sf::Keyboard::Escape)
                {   
                    changeStage(GameStages::Menu);
                }
                break;
        }
    }
}

void Game::update()
{
    switch (m_stage)
    {
    case GameStages::Menu:
        m_menu->update(clock.getElapsedTime().asSeconds());
        break;
    case GameStages::InGame:
        m_world->update();
        break;
    }
}

void Game::render()
{
    m_window->clear();
    switch (m_stage)
    {
    case GameStages::Menu:
        m_window->draw(*m_menu);
        break;
    case GameStages::InGame:
        m_window->draw(*m_world);
        break;
    }
    m_window->display();
}

Game::~Game()
{
    delete m_world;
    delete m_menu;
    delete m_window;
}

void Game::changeStage(int to)
{
    if (m_stage == GameStages::Menu)
    {
        if (to == GameStages::InGame)
        {
            m_world = new World(m_cells_number);
            m_window->setFramerateLimit(m_speed);
            m_stage = to;
            m_window->setMouseCursorVisible(false);
        }
    }
    else if (m_stage == GameStages::InGame)
    {
        if (to == GameStages::Menu)
        {
            delete m_world;
            m_world = nullptr;
            m_window->setFramerateLimit(144);
            m_stage = to;
            m_window->setMouseCursorVisible(true);
        }
    }
}