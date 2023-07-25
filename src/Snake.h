#pragma once
#include <SFML/Graphics.hpp>
#include "DataCell.h"
#include <vector>

enum Direction { None, Up, Down, Left, Right };

class Snake
{
private:
    std::vector<DataCell> m_body;
    Direction m_dir;
public:
    Snake();
    void reset();
    void update();
    void move();
    void grow();

    void ProcessInput(const sf::Keyboard::Key& key);
    void SetDirection(Direction dir) { m_dir = dir; }

    const sf::Vector2i& GetHeadPosition() { return m_body[0].GetPosition(); }
    const std::vector<DataCell>& GetBody() { return m_body; }
    
    // For future:
    // void checkCollision();
    // void cut(int number_of_segments);
};