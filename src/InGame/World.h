#pragma once 
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Grid.h"
#include "GameOverScreen.h"
#include "Fruits.h"

class World : public sf::Drawable
{
private:
    Snake m_snake;
    Fruits m_fruits;

    sf::Vector2f m_cell_size;
    sf::Vector2i m_cellsNumber;

    Grid m_grid;

    sf::Shader* m_light;

    bool m_isOver = false;
    GameOverScreen* m_OverScreen;

    void updateShaders();

    std::vector<sf::Vector2i> validFruitPositions;
    void updateValidFruitPositions();

    int scores = 0;
public:
    World(const sf::Vector2i& cellsNumber);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void update();
    void processInput(const sf::Keyboard::Key& key);
    void CheckColision();
};