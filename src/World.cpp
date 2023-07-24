#include "World.h"

World::World(const sf::Vector2f cell_size, const int& cells_number)
    : m_snake{cell_size}, m_fruit{cell_size}, m_cells_number{cells_number}, m_number_generator{0, cells_number - 1}
{

}

void World::update()
{
    m_snake.update();
    CheckColision();
}

void World::processInput(const sf::Keyboard::Key& key)
{
    m_snake.ProcessInput(key);
}

void World::CheckColision()
{
    if (m_snake.GetHeadPositionXY() == m_fruit.m_body.GetPositionXY())
    {
        m_snake.grow();
        RespawnFruit();
    }
}

void World::RespawnFruit()
{
    m_fruit.m_body.SetPosition(m_number_generator.generateNumber(), m_number_generator.generateNumber());   
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_fruit, states);
    target.draw(m_snake, states);
}