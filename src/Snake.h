#pragma once
#include <SFML/Graphics.hpp>
#include "SnakeSegment.h"
#include <vector>

enum Direction { None, Up, Down, Left, Right };

typedef std::vector<SnakeSegment> SnakeContainer;

class Snake : public sf::Drawable
{
private:
    SnakeContainer m_body;
    
    sf::Vector2f m_segment_size;
    Direction m_dir;

public:
    Snake(sf::Vector2f segment_size);
    void reset();
    void update();
    void move();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void ProcessInput(const sf::Keyboard::Key& key);
    void SetDirection(Direction dir) { m_dir = dir; }
    
    // void grow();
    // void checkCollision();
    // void cut(int number_of_segments);
};