#pragma once 
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "NumberGenerator.h"
#include "Grid.h"
#include "PositionManager.h"
#include "ShaderManager.h"

class World : public sf::Drawable
{
private:
    PositionManager* m_positionConverter;
    ShaderManager* m_shaderManager;

    Snake m_snake;
    DataCell m_fruit;
    NumberGenerator m_number_generator;

    sf::Vector2f m_cell_size;
    sf::Vector2i m_cellsNumber;

    Grid m_grid;

    sf::Shader* m_light;

    void updateShaders();

    std::vector<sf::Vector2i> validFruitPositions;
    void updateValidFruitPositions();
public:
    World(PositionManager* converterPtr, ShaderManager* shaderManagerPtr, const sf::Vector2i& cellsNumber);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void update();
    void processInput(const sf::Keyboard::Key& key);
    void CheckColision();

    void RespawnFruit();

    void resize();
};