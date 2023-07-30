#include "Snake.h"
#include <iostream>
#include <cmath>

Snake::Snake(const int& number_of_cells)    
    : m_cells_number{number_of_cells}
{
    reset();
}

void Snake::reset()
{
    m_body.clear();

    m_body.push_back(DataCell(5, 5, sf::Color::Yellow));
    m_body.push_back(DataCell(5, 6));
    m_body.push_back(DataCell(5, 7));

    for (int i = 0; i < m_body.size(); i++)
    {
        if (i != 0)
        {
            UpdateColor(i);
        }  
    }
    SetDirection(None);
}

void Snake::UpdateColor(const int& index) 
{
    if (index != 0)
    {
        sf::Color prevColor = m_body[index - 1].GetColor();

        sf::Vector2i currentPosition = m_body[index].GetPosition();
        sf::Vector2i prevPosition = m_body[index - 1].GetPosition();

        float distance = std::sqrt(std::pow(currentPosition.x - prevPosition.x, 2) + std::pow(currentPosition.y - prevPosition.y, 2));
        float colorStep = distance * 25.f;

        sf::Color newColor(
            static_cast<sf::Uint8>(std::max(0, static_cast<int>(prevColor.r) - static_cast<int>(colorStep))),
            static_cast<sf::Uint8>(std::min(255, static_cast<int>(prevColor.g) + static_cast<int>(colorStep))),
            static_cast<sf::Uint8>(std::max(0, static_cast<int>(prevColor.b) - static_cast<int>(colorStep)))
        );

        m_body[index].SetColor(newColor);
    }   
}

void Snake::update()
{
    if (m_body.empty() == false && m_dir != None)
    {
        move();
        checkCollision();
    }
}

void Snake::move()
{
    if (m_dir == Direction::None) return;

    for (int i = m_body.size() - 1; i > 0; i--)
    {
        m_body[i].SetPosition(m_body[i - 1].GetPosition());
    }

    if (m_dir == Direction::Left) m_body[0].AddPosition(-1, 0);
    else if (m_dir == Direction::Right) m_body[0].AddPosition(1, 0);
    else if (m_dir == Direction::Up) m_body[0].AddPosition(0, -1);
    else if (m_dir == Direction::Down) m_body[0].AddPosition(0, 1);
}

void Snake::checkCollision()
{
    if (m_body.size() >= 5)
    {
        const DataCell& head = m_body[0];
        for (int i = 1; i < m_body.size(); i++)
        {
            if (head.GetPosition() == m_body[i].GetPosition())
            {
                int number = m_body.size() - i;
                cut(number);
                return;
            }
        }
    }
}

void Snake::cut(const int& number_of_segments)
{
    for (int i = 0; i < number_of_segments; i++)
    {
        m_body.pop_back();
    }
}

void Snake::grow()
{  
    const DataCell& tail = m_body[m_body.size() - 1];
    sf::Vector2i tail_pos = tail.GetPosition();
    if (m_body.size() > 1)
    {
        const DataCell& pre_tail = m_body[m_body.size() - 2];
        sf::Vector2i pre_tail_pos = pre_tail.GetPosition();
        if (tail_pos.x == pre_tail_pos.x)
        {
            if (tail_pos.y > pre_tail_pos.y)    
            {
                if (tail_pos.y == m_cells_number - 1)
                {
                    if (tail_pos.x + 1 <= m_cells_number - 1)
                    {
                        m_body.push_back(DataCell(tail_pos.x + 1, tail_pos.y));
                        UpdateColor(m_body.size() - 1);
                    }
                    else 
                    {
                        m_body.push_back(DataCell(tail_pos.x - 1, tail_pos.y));
                        UpdateColor(m_body.size() - 1);
                    }
                    
                }
                else 
                {
                    m_body.push_back(DataCell(tail_pos.x, tail_pos.y + 1));
                    UpdateColor(m_body.size() - 1);
                }
                
            }
            else
            {
                if (tail_pos.y == 0)
                {
                    if (tail_pos.x + 1 <= m_cells_number - 1)
                    {
                        m_body.push_back(DataCell(tail_pos.x + 1, tail_pos.y));
                        UpdateColor(m_body.size() - 1);
                    }
                    else
                    {
                        m_body.push_back(DataCell(tail_pos.x - 1, tail_pos.y));
                        UpdateColor(m_body.size() - 1);
                    }
                }
                else
                {
                    m_body.push_back(DataCell(tail_pos.x, tail_pos.y - 1));
                    UpdateColor(m_body.size() - 1);
                }
                
            }
        }
        else if (tail_pos.y == pre_tail_pos.y)
        {
            if (tail_pos.x > pre_tail_pos.x)
            {
                if (tail_pos.x == m_cells_number - 1)
                {
                    if (tail_pos.y + 1 <= m_cells_number - 1)
                    {
                        m_body.push_back(DataCell(tail_pos.x, tail_pos.y + 1));
                        UpdateColor(m_body.size() - 1);
                    }
                    else
                    {
                        m_body.push_back(DataCell(tail_pos.x, tail_pos.y - 1));
                        UpdateColor(m_body.size() - 1);
                    }
                }
                else 
                {
                    m_body.push_back(DataCell(tail_pos.x + 1, tail_pos.y));
                    UpdateColor(m_body.size() - 1);
                }
                
            }
            else
            {
                if (tail_pos.x == 0)
                {
                    if (tail_pos.y + 1 <= m_cells_number - 1)
                    {
                        m_body.push_back(DataCell(tail_pos.x, tail_pos.y + 1));
                        UpdateColor(m_body.size() - 1);
                    }
                    else
                    {
                        m_body.push_back(DataCell(tail_pos.x, tail_pos.y - 1));
                        UpdateColor(m_body.size() - 1);
                    }
                }
                else
                {
                    m_body.push_back(DataCell(tail_pos.x - 1, tail_pos.y));
                    UpdateColor(m_body.size() - 1);
                }
            }
        }
    }
    // else 
    // {
    //     if (m_dir == Direction::Down)   m_body.push_back(DataCell(tail_pos.x, tail_pos.y - 1, sf::Color::Green));
    //     else if (m_dir == Direction::Up)    m_body.push_back(DataCell(tail_pos.x, tail_pos.y + 1, sf::Color::Green));
    //     else if (m_dir == Direction::Left)    m_body.push_back(DataCell(tail_pos.x + 1, tail_pos.y, sf::Color::Green));
    //     else if (m_dir == Direction::Right)    m_body.push_back(DataCell(tail_pos.x - 1, tail_pos.y, sf::Color::Green));
    // }
}

void Snake::ProcessInput(const sf::Keyboard::Key& key) 
{
    if ((key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::A) && CanMove(Direction::Left) == true) SetDirection(Direction::Left);
    else if ((key == sf::Keyboard::Key::Right || key == sf::Keyboard::Key::D) && CanMove(Direction::Right) == true) SetDirection(Direction::Right);
    else if ((key == sf::Keyboard::Up || key == sf::Keyboard::Key::W) && CanMove(Direction::Up) == true) SetDirection(Direction::Up);
    else if ((key == sf::Keyboard::Key::Down || key == sf::Keyboard::Key::S) && CanMove(Direction::Down) == true) SetDirection(Direction::Down);
}

bool Snake::CanMove(const Direction& dir)
{
    const sf::Vector2i& head = m_body[0].GetPosition();
    const sf::Vector2i& pre_head = m_body[1].GetPosition();

    if (dir == Direction::Up)
    {
        if (!(head.y > pre_head.y))
            return true;
        return false;
    }
    else if (dir == Direction::Down)
    {
        if (!(head.y < pre_head.y))
            return true;
        return false;
    }
    else if (dir == Direction::Left)
    {
        if (!(head.x > pre_head.x))
            return true;
        return false;
    }
    else if (dir == Direction::Right)
    {  
        if (!(head.x < pre_head.x))
            return true;
        return false;
    }
}