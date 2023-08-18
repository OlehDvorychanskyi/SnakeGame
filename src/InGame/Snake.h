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
    bool m_alive = true;

    void UpdateColor(int index);
    bool CanMove(Direction dir);
    sf::Color HSVtoRGB(sf::Vector3f hsv);
    sf::Vector3f RGBtoHSV(const sf::Color& rgbColor);
public:
    Snake(const sf::Vector2i& number_of_cells);
    void reset();
    void update();
    void move();
    void grow();

    void ProcessInput(const sf::Keyboard::Key& key);
    void SetDirection(Direction dir) { m_dir = dir; }

    DataCell& GetHead() { return m_body.at(0); }
    sf::Vector2i GetHeadPosition() { return m_body.at(0).GetPosition(); }
    void MoveBackward();
    std::vector<DataCell>& GetBody() { return m_body; }
    
    void checkCollision();
    void cut(const int& number_of_segments);

    bool FindPositionInSnake(sf::Vector2i position);

    int getScores();

    bool isAlive() { return m_alive; }
};