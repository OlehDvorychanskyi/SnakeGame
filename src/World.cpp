#include "World.h"

World::World(const sf::Vector2f cell_size, const int& cells_number)
    : m_cells_number{cells_number}, m_number_generator{0, cells_number - 1}, m_grid{cell_size, cells_number}, m_fruit{0, 0, sf::Color::Red}
{
}

void World::update()
{
    m_snake.update();
    CheckColision();

    m_grid.clear();
    m_grid.update(m_snake.GetBody());
    m_grid.update(m_fruit);
}

void World::processInput(const sf::Keyboard::Key& key)
{
    m_snake.ProcessInput(key);
}

void World::CheckColision()
{
    if (m_snake.GetHeadPosition() == m_fruit.GetPosition())
    {
        m_snake.grow();
        RespawnFruit();
    }

    if (m_snake.GetHeadPosition().x < 0 || m_snake.GetHeadPosition().x >= m_cells_number || m_snake.GetHeadPosition().y < 0 || m_snake.GetHeadPosition().y >= m_cells_number)
    {
        m_snake.reset();
    }
}

void World::RespawnFruit()
{
    m_fruit.SetPosition(m_number_generator.generateNumber(), m_number_generator.generateNumber());
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_grid, states);
}