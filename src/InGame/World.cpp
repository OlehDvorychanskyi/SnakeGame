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
    m_fruits.generate(ConfigLoader::Config->get<int>("World", "fruitsNumber", 5), validFruitPositions, m_cell_size);

    m_light = &ResourceHolders::ShaderHolder->get("World");
    m_light->setUniform("snakeLightColor", sf::Vector3f(m_snake.GetHead().GetColor().r, m_snake.GetHead().GetColor().g, m_snake.GetHead().GetColor().b));
    m_light->setUniform("cellSize", m_cell_size);
    m_fruits.setLightColorArray(m_light);
    m_fruits.setLightPositionArray(m_light, m_cell_size);
}

void World::update()
{
    if (m_isOver == false)
    {
        m_snake.update();
        CheckColision();

        updateValidFruitPositions();
        m_fruits.checkFruitsNumber(validFruitPositions, m_cell_size);
        m_fruits.updateShapes(m_cell_size);
        updateShaders();

        m_grid.clear();
        m_grid.update(m_snake.GetBody());
    }
}

void World::updateShaders()
{
    m_light->setUniform("snakeLightPosition", PositionManager::toCenterPositionInOpenGL(m_snake.GetBody().at(0).GetFloatPosition(), m_cell_size));
    m_fruits.setLightColorArray(m_light);
    m_fruits.setLightPositionArray(m_light, m_cell_size);
}

void World::processInput(const sf::Keyboard::Key& key)
{
    m_snake.ProcessInput(key);
    if (m_isOver == true && key == sf::Keyboard::Key::Space)
    {
        m_isOver = false;
        m_snake.reset();
        m_fruits.reset(); // clear fruits
        updateValidFruitPositions();
        m_fruits.generate(ConfigLoader::Config->get<int>("World", "fruitsNumber", 5), validFruitPositions, m_cell_size);
    }
}

void World::CheckColision()
{
    if (m_fruits.checkCollision(m_snake.GetHeadPosition()) != sf::Vector2i(-1, -1))
    {
        m_snake.grow();
        updateValidFruitPositions();
        m_fruits.respawnSingle(m_snake.GetHeadPosition(), NumberGenerator::generatePosition(validFruitPositions));
    }

    if (m_snake.isAlive() == false || m_snake.getScores() + 1 == m_cellsNumber.x * m_cellsNumber.y)
    {
        m_isOver = true;
        m_OverScreen.m_scoresText.setString("Your score is " + std::to_string(m_snake.getScores()));
        m_OverScreen.m_scoresText.setOrigin(m_OverScreen.m_scoresText.getGlobalBounds().getSize() / 2.f + m_OverScreen.m_scoresText.getLocalBounds().getPosition());
        m_OverScreen.m_scoresText.setPosition(m_OverScreen.darkBackground.getPosition().x + (m_OverScreen.darkBackground.getSize().x / 2.f), m_OverScreen.darkBackground.getPosition().y + (m_OverScreen.darkBackground.getSize().y / 2.f) + PositionManager::percentToPixel({0, 5}).y);
    }
}

void World::updateValidFruitPositions()
{
    validFruitPositions.clear();
    for (int i = 0; i < m_cellsNumber.x; i++)
    {
        for (int j = 0; j < m_cellsNumber.y; j++)
        {   
            if (m_snake.FindPositionInSnake({i, j}) == false 
                && m_fruits.checkCollision({i, j}) == sf::Vector2i(-1, -1))
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
        target.draw(m_OverScreen);
}