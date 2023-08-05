#pragma once
#include <SFML/Graphics.hpp>
#include "DataCell.h"
#include <vector>

enum Direction { None, Up, Down, Left, Right };

class Snake
{
private:
    std::vector<DataCell> m_body;
    sf::Vector2i m_cells_number;
    Direction m_dir;

    void UpdateColor(const int& index);
    bool CanMove(const Direction& dir);
public:
    Snake(const sf::Vector2i& number_of_cells);
    void reset();
    void update();
    void move();
    void grow();

    void ProcessInput(const sf::Keyboard::Key& key);
    void SetDirection(Direction dir) { m_dir = dir; }

    const sf::Vector2i& GetHeadPosition() { return m_body.front().GetPosition(); }
    std::vector<DataCell>& GetBody() { return m_body; }
    
    void checkCollision();
    void cut(const int& number_of_segments);
};