#include "Snake.h"
#include <iostream>

Snake::Snake()
{
    reset();
}

void Snake::reset()
{
    m_body.clear();

    m_body.push_back(DataCell(5, 5, sf::Color::Green));
    m_body.push_back(DataCell(5, 6, sf::Color::Green));
    m_body.push_back(DataCell(5, 7, sf::Color::Green));

    for (int i = 0; i < m_body.size(); i++)
    {
        if (i == 0)
            m_body[i].SetColor(sf::Color::Yellow);
        else
            m_body[i].SetColor(sf::Color::Green);
    }
    SetDirection(None);
}

void Snake::update()
{
    if (m_body.empty() == false && m_dir != None)
    {
        move();
    }
}

void Snake::move()
{
    for (int i = m_body.size() - 1; i > 0; i--)
    {
        m_body[i].SetPosition(m_body[i - 1].GetPosition());
    }

    if (m_dir == Direction::Left) m_body[0].AddPosition(-1, 0);
    else if (m_dir == Direction::Right) m_body[0].AddPosition(1, 0);
    else if (m_dir == Direction::Up) m_body[0].AddPosition(0, -1);
    else if (m_dir == Direction::Down) m_body[0].AddPosition(0, 1);
}

void Snake::grow() // Bug here: add cell outside the map
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
                if (tail_pos.y == 9) std::cout << "Outside the map" << std::endl;
                m_body.push_back(DataCell(tail_pos.x, tail_pos.y + 1, sf::Color::Green));
            }
            else
            {
                if (tail_pos.y == 0) std::cout << "Outside the map" << std::endl;
                m_body.push_back(DataCell(tail_pos.x, tail_pos.y - 1, sf::Color::Green));
            }
        }
        else if (tail_pos.y == pre_tail_pos.y)
        {
            if (tail_pos.x > pre_tail_pos.x)
            {
                if (tail_pos.x == 9) std::cout << "Outside the map" << std::endl;
                m_body.push_back(DataCell(tail_pos.x + 1, tail_pos.y, sf::Color::Green));
            }
            else
            {
                if (tail_pos.x == 0) std::cout << "Outside the map" << std::endl;
                m_body.push_back(DataCell(tail_pos.x - 1, tail_pos.y, sf::Color::Green));
            }
        }
    }
    else 
    {
        if (m_dir == Direction::Down)   m_body.push_back(DataCell(tail_pos.x, tail_pos.y - 1, sf::Color::Green));
        else if (m_dir == Direction::Up)    m_body.push_back(DataCell(tail_pos.x, tail_pos.y + 1, sf::Color::Green));
        else if (m_dir == Direction::Left)    m_body.push_back(DataCell(tail_pos.x + 1, tail_pos.y, sf::Color::Green));
        else if (m_dir == Direction::Right)    m_body.push_back(DataCell(tail_pos.x - 1, tail_pos.y, sf::Color::Green));
    }
}

void Snake::ProcessInput(const sf::Keyboard::Key& key)
{
    if (key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::A) SetDirection(Direction::Left);
    else if (key == sf::Keyboard::Key::Right || key == sf::Keyboard::Key::D) SetDirection(Direction::Right);
    else if (key == sf::Keyboard::Up || key == sf::Keyboard::Key::W) SetDirection(Direction::Up);
    else if (key == sf::Keyboard::Key::Down || key == sf::Keyboard::Key::S) SetDirection(Direction::Down);
}