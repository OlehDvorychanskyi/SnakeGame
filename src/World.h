#pragma once 
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Fruit.h"
#include "NumberGenerator.h"

class World : public sf::Drawable
{
private:
    Snake m_snake;
    Fruit m_fruit;
    NumberGenerator m_number_generator;
    int m_cells_number;
public:
    World(const sf::Vector2f cell_size, const int& cells_number);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void update();
    void processInput(const sf::Keyboard::Key& key);
    void CheckColision();

    void RespawnFruit();
};