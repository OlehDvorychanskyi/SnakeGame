#include "World.h"
#include <iostream>

World::World(PositionConverter& converterRef)
    : m_number_generator{0, converterRef.getCellsNumber() - 1}, m_grid{converterRef.getCellSize(), converterRef.getCellsNumber()}, 
    m_fruit{0, 0, sf::Color::Red}, m_snake{converterRef.getCellsNumber()}, m_light("shaders/CellShader.frag")
{
    m_converter = &converterRef;

    m_light.SetColor("snakeLightColor", m_snake.GetBody().at(0).GetColor());
    m_light.SetColor("fruitLightColor", m_fruit.GetColor());
}

void World::update()
{
    m_snake.update();
    CheckColision();

    updateShaders();

    m_grid.clear();
    m_grid.update(m_snake.GetBody());
    m_grid.update(m_fruit);
}

void World::updateShaders()
{
    m_light.SetPosition("snakeLightPosition", m_converter->toLightPositionInShader(m_snake.GetBody().at(0).GetPosition()));
    m_light.SetPosition("fruitLightPosition", m_converter->toLightPositionInShader(m_fruit.GetPosition()));
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

    if (m_snake.GetHeadPosition().x < 0 || m_snake.GetHeadPosition().x >= m_converter->getCellsNumber() || m_snake.GetHeadPosition().y < 0 || m_snake.GetHeadPosition().y >= m_converter->getCellsNumber())
    {
        m_snake.reset();
    }
}

void World::RespawnFruit()
{
    updateValidFruitPositions();
    m_fruit.SetPosition(m_number_generator.generatePosition(validFruitPositions));
}

void World::updateValidFruitPositions()
{
    validFruitPositions.clear();
    for (int i = 0; i < m_converter->getCellsNumber(); i++)
    {
        for (int j = 0; j < m_converter->getCellsNumber(); j++)
        {
            if (std::find(m_snake.GetBody().begin(), m_snake.GetBody().end(), sf::Vector2i(i, j)) == m_snake.GetBody().end())
            {
                validFruitPositions.push_back(sf::Vector2i(i, j));
            }
        }
    }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_grid, &m_light.get());
}

void World::resize()
{
    m_grid.resize(m_converter->getCellSize(), m_converter->getCellsNumber());
}