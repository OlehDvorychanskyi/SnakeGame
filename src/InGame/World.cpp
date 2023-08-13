#include "World.h"
#include <iostream>
#include <PositionManager.h>
#include <NumberGenerator.h>
#include <ResourceHolder.h>
#include <ConfigLoader.h>

World::World(const sf::Vector2i& cellsNumber)
    : m_snake(cellsNumber), m_grid{PositionManager::getCellSize(cellsNumber), cellsNumber}
{
    m_cellsNumber = cellsNumber;
    m_cell_size = PositionManager::getCellSize(cellsNumber);

    updateValidFruitPositions();
    m_fruits.spawn(ConfigLoader::Config->get<int>("World", "fruitsNumber", 5), validFruitPositions, m_cell_size);

    m_light = &ResourceHolders::ShaderHolder->get("World");
    m_light->setUniform("snakeLightColor", sf::Vector3f(m_snake.GetBody().at(0).GetColor().r, m_snake.GetBody().at(0).GetColor().g, m_snake.GetBody().at(0).GetColor().b));
    m_light->setUniform("cellSize", m_cell_size);
    m_fruits.setLightArray(m_light, m_cell_size);
}

void World::update()
{
    if (m_isOver == false)
    {
        m_snake.update();
        CheckColision();

        m_fruits.updateShapes(m_cell_size);
        updateShaders();

        m_grid.clear();
        m_grid.update(m_snake.GetBody());
    }
}

void World::updateShaders()
{
    m_light->setUniform("snakeLightPosition", PositionManager::toCenterPositionInOpenGL(m_snake.GetBody().at(0).GetFloatPosition(), m_cell_size));
    m_fruits.setLightArray(m_light, m_cell_size);
}

void World::processInput(const sf::Keyboard::Key& key)
{
    m_snake.ProcessInput(key);
    if (m_isOver == true && key == sf::Keyboard::Key::Space)
    {
        m_isOver = false;
        m_snake.reset();
        updateValidFruitPositions();
        m_fruits.respawnAll(validFruitPositions);
    }
}

void World::CheckColision()
{
    if (m_fruits.checkCollision(m_snake.GetHeadPosition()) != sf::Vector2i(-1, -1))
    {
        // colision detected
        updateValidFruitPositions();
        m_fruits.respawnSingle(m_snake.GetHeadPosition(), NumberGenerator::generatePosition(validFruitPositions));
        m_snake.grow();
        scores++;
    }

    if (m_snake.GetHeadPosition().x < 0 || m_snake.GetHeadPosition().x >= m_cellsNumber.x || m_snake.GetHeadPosition().y < 0 || m_snake.GetHeadPosition().y >= m_cellsNumber.y)
    {
        // Game Over
        m_isOver = true;
        if (m_snake.GetHeadPosition().x < 0)
            m_snake.GetBody().at(0).AddPosition(1, 0);
        else if (m_snake.GetHeadPosition().x >= m_cellsNumber.x)
            m_snake.GetBody().at(0).AddPosition(-1, 0);
        else if (m_snake.GetHeadPosition().y < 0)
            m_snake.GetBody().at(0).AddPosition(0, 1);
        else if (m_snake.GetHeadPosition().y >= m_cellsNumber.y)
            m_snake.GetBody().at(0).AddPosition(0, -1);

        m_OverScreen = new GameOverScreen(scores);
        scores = 0;
    }
}

void World::updateValidFruitPositions()
{
    validFruitPositions.clear();
    for (int i = 0; i < m_cellsNumber.x; i++)
    {
        for (int j = 0; j < m_cellsNumber.y; j++)
        {   
            if (std::find(m_snake.GetBody().begin(), m_snake.GetBody().end(), sf::Vector2i(i, j)) == m_snake.GetBody().end() 
                && std::find(m_fruits.GetBody().begin(), m_fruits.GetBody().end(), sf::Vector2i(i, j)) == m_fruits.GetBody().end())
            {
                validFruitPositions.push_back(sf::Vector2i(i, j));
            }
        }
    }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_grid, &(*m_light));
    target.draw(m_fruits);
    if (m_isOver == true)
        target.draw(*m_OverScreen);
}