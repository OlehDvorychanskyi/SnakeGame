#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode(800, 800), "Snake"), 
    m_positionConvertor(m_window.getSize(), sf::Vector2f((float)m_window.getSize().x / (float)m_cells_number, (float)m_window.getSize().y / (float)m_cells_number), m_cells_number),
    m_world(m_positionConvertor)
{
    m_window.setFramerateLimit(10);
    m_stages = GameStage::InGame;
}

void Game::run()
{
    while (m_window.isOpen() == true)
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            m_window.close();
        }

        switch (m_stages)
        {
            case GameStage::MainMenu:
                break;
            case GameStage::InGame:
                if (event.type == sf::Event::KeyPressed)
                {
                    m_world.processInput(event.key.code);
                }
                if (event.type == sf::Event::Resized)
                {
                    m_positionConvertor.resize(event.size.width, event.size.height);
                    m_world.resize();
                }
                break;
        }

    }
}

void Game::update()
{
    switch (m_stages)
    {
    case GameStage::MainMenu:
        break;
    case GameStage::InGame:
        m_world.update();
        break;
    }
}

void Game::render()
{
    switch (m_stages)
    {
    case GameStage::MainMenu:
        m_window.clear();
        m_window.display();
        break;
    case GameStage::InGame:
        m_window.clear();
        m_window.draw(m_world);
        m_window.display();
        break;
    }

}