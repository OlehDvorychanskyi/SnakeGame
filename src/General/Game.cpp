#include "Game.h"
#include <iostream>

Game::Game()
{
    config.load("config.ini");

    unsigned width = config.get<unsigned>("Window", "width", 800U);
    unsigned height = config.get<unsigned>("Window", "height", 800U);

    if (config.get<bool>("Window", "fullscreen", false) == false)
        m_window = new sf::RenderWindow(sf::VideoMode(width, height), "Snake");
    else    
        m_window = new sf::RenderWindow(sf::VideoMode(width, height), "Snake", sf::Style::Fullscreen);
    
    int WidthCells = config.get<int>("World", "widthCells", 10);
    int HeightCells = config.get<int>("World", "heightCells", 10);
    m_cells_number = {WidthCells, HeightCells};

    m_positionManager = new PositionManager(m_window);
    m_shaderManager = new ShaderManager();
    m_fontManager = new FontManager();
    
    m_shaderManager->load<sf::Shader::Type>("World", "shaders/CellShader.frag", sf::Shader::Fragment);
    m_shaderManager->load<sf::Shader::Type>("SnakeEffect", "shaders/SnakeEffect.frag", sf::Shader::Fragment);

    m_fontManager->load("MainMenuFont", "fonts/Clancy-Free-BF648d4e44231d4.otf");

    m_stage = GameStages::Menu;
    m_menu = new MainMenu(m_positionManager, m_shaderManager, m_fontManager);
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
            sf::View newView({(float)event.size.width / 2.f, (float)event.size.height / 2.f}, {event.size.width, event.size.height});
            m_window->setView(newView);

            m_positionManager->resize(event.size.width, event.size.height);

            if (m_stage == GameStages::InGame)
            {
                delete m_world;
                m_world = new World(m_positionManager, m_shaderManager, m_cells_number);
            } 
            else if (m_stage == GameStages::Menu)
            {
                delete m_menu;
                m_menu = new MainMenu(m_positionManager, m_shaderManager, m_fontManager);
            }
        }

        if (event.type == sf::Event::Closed)
            m_window->close();

        switch (m_stage)
        {
            case GameStages::Menu:
                m_menu->processInput(event);
                if (m_menu->isButtonPressed("Start")) 
                    changeStage(m_stage, GameStages::InGame);
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
                    changeStage(m_stage, GameStages::Menu);
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
    delete m_positionManager;
    delete m_shaderManager;
    delete m_fontManager;
    delete m_window;
}

void Game::changeStage(const int& from, const int& to)
{
    if (from == GameStages::Menu)
    {
        if (to == GameStages::InGame)
        {
            m_world = new World(m_positionManager, m_shaderManager, m_cells_number);
            m_window->setFramerateLimit(10);
            m_stage = to;
        }
    }
    else if (from == GameStages::InGame)
    {
        if (to == GameStages::Menu)
        {
            delete m_world;
            m_world = nullptr;
            m_window->setFramerateLimit(0);
            m_stage = to;
        }
    }
}