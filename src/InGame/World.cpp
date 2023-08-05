#include "World.h"
#include <iostream>

World::World(PositionManager* converterPtr, ShaderManager* shaderManagerPtr, const sf::Vector2i& cellsNumber)
    : m_snake(cellsNumber), m_fruit(0, 0, sf::Color::Red), m_grid{converterPtr->getCellSize(cellsNumber), cellsNumber}
{
    m_positionConverter = converterPtr;
    m_shaderManager = shaderManagerPtr;
    m_cellsNumber = cellsNumber;
    m_cell_size = converterPtr->getCellSize(cellsNumber);

    m_light = &m_shaderManager->get("World");
    m_light->setUniform("snakeLightColor", sf::Vector3f(m_snake.GetBody().at(0).GetColor().r, m_snake.GetBody().at(0).GetColor().g, m_snake.GetBody().at(0).GetColor().b));
    m_light->setUniform("fruitLightColor", sf::Vector3f(m_fruit.GetColor().r, m_fruit.GetColor().g, m_fruit.GetColor().b));
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
    m_light->setUniform("snakeLightPosition", m_positionConverter->toCenterPositionInOpenGL(m_snake.GetBody().at(0).GetFloatPosition(), m_cell_size));
    m_light->setUniform("fruitLightPosition", m_positionConverter->toCenterPositionInOpenGL(m_fruit.GetFloatPosition(), m_cell_size));
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

    if (m_snake.GetHeadPosition().x < 0 || m_snake.GetHeadPosition().x >= m_cellsNumber.x || m_snake.GetHeadPosition().y < 0 || m_snake.GetHeadPosition().y >= m_cellsNumber.y)
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
    for (int i = 0; i < m_cellsNumber.x; i++)
    {
        for (int j = 0; j < m_cellsNumber.y; j++)
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
    target.draw(m_grid, &(*m_light));
}

// void World::resize()
// {
//     m_grid.resize(m_positionConverter->getCellSize(), m_converter->getCellsNumber());
// }