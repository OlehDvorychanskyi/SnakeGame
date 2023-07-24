#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include <vector>

enum Direction { None, Up, Down, Left, Right };

class Snake : public sf::Drawable
{
private:
    std::vector<Cell> m_body;
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

    const sf::Vector2f GetHeadPositionPX() { return m_body[0].GetPositionPX(); }
    const sf::Vector2i GetHeadPositionXY() { return m_body[0].GetPositionXY(); }
    
    void grow();
    // void checkCollision();
    // void cut(int number_of_segments);
};