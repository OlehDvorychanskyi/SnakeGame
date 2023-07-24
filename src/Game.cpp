#include "Game.h"

#define NUMBER_OF_CELLS 25

Game::Game()
    : m_window(sf::VideoMode(800, 800), "Snake"), m_world(sf::Vector2f(m_window.getSize().x / NUMBER_OF_CELLS, m_window.getSize().y / NUMBER_OF_CELLS), NUMBER_OF_CELLS)
{
    m_window.setFramerateLimit(7);
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
        if (event.type == sf::Event::KeyPressed)
        {
            m_world.processInput(event.key.code);
        }
    }
}

void Game::update()
{
    m_world.update();
}

void Game::render()
{
    m_window.clear();
    m_window.draw(m_world);
    m_window.display();
}