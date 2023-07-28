#pragma once 
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "NumberGenerator.h"

#include "Grid.h"

#include "LightShader.h"

#include "PositionConverter.h"

class World : public sf::Drawable
{
private:
    PositionConverter* m_converter;

    Snake m_snake;
    DataCell m_fruit;
    NumberGenerator m_number_generator;
    sf::Vector2f m_cells_size;

    Grid m_grid;

    LightShader m_light;

    


    void updateShaders();


public:
    World(PositionConverter& converterRef);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void update();
    void processInput(const sf::Keyboard::Key& key);
    void CheckColision();

    void RespawnFruit();
};