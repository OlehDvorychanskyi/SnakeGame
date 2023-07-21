#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Snake")
{

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
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code ==sf::Keyboard::Escape))
        {
            m_window.close();
        }
    }
}

void Game::update()
{

}

void Game::render()
{
    m_window.clear();
    m_window.display();
}