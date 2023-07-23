#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Snake"), m_snake(sf::Vector2f(30.f, 30.f))
{
    m_window.setFramerateLimit(5);
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
            m_snake.ProcessInput(event.key.code);
        }
    }
}

void Game::update()
{
    m_snake.update();
}

void Game::render()
{
    m_window.clear();
    m_window.draw(m_snake);
    m_window.display();
}