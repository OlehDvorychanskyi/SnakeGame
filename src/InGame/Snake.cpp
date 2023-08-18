#include "Snake.h"
#include <iostream>
#include <cmath>
#include <algorithm>

sf::Color Snake::HSVtoRGB(sf::Vector3f hsv) 
{
    float c = hsv.z * hsv.y;
    float x = c * (1 - std::abs(std::fmod(hsv.x / 60, 2) - 1));
    float m = hsv.z - c;
    
    if (hsv.x >= 0 && hsv.x < 60) {
        return sf::Color((c + m) * 255, (x + m) * 255, m * 255);
    } else if (hsv.x >= 60 && hsv.x < 120) {
        return sf::Color((x + m) * 255, (c + m) * 255, m * 255);
    } else if (hsv.x >= 120 && hsv.x < 180) {
        return sf::Color(m * 255, (c + m) * 255, (x + m) * 255);
    } else if (hsv.x >= 180 && hsv.x < 240) {
        return sf::Color(m * 255, (x + m) * 255, (c + m) * 255);
    } else if (hsv.x >= 240 && hsv.x < 300) {
        return sf::Color((x + m) * 255, m * 255, (c + m) * 255);
    } else {
        return sf::Color((c + m) * 255, m * 255, (x + m) * 255);
    }
}

sf::Vector3f Snake::RGBtoHSV(const sf::Color& rgbColor) {
    float r = rgbColor.r / 255.0f;
    float g = rgbColor.g / 255.0f;
    float b = rgbColor.b / 255.0f;

    float cMax = std::max(r, std::max(g, b));
    float cMin = std::min(r, std::min(g, b));
    float delta = cMax - cMin;

    float hue = 0;
    if (delta != 0) {
        if (cMax == r) {
            hue = 60 * ((g - b) / delta);
        } else if (cMax == g) {
            hue = 60 * ((b - r) / delta + 2);
        } else if (cMax == b) {
            hue = 60 * ((r - g) / delta + 4);
        }

        if (hue < 0) {
            hue += 360;
        }
    }

    float saturation = (cMax != 0) ? (delta / cMax) : 0;
    float value = cMax;

    return sf::Vector3f(hue, saturation, value);
}

Snake::Snake(const sf::Vector2i& number_of_cells)    
    : m_cells_number{number_of_cells}
{
    reset();
}

void Snake::reset()
{
    m_body.clear();
    m_body.push_back(DataCell(5, 5, sf::Color::Red));
    SetDirection(None);
    m_alive = true;
}

void Snake::UpdateColor(int index) 
{
    if (index != 0)
    {
        sf::Color prevColor = m_body[index - 1].GetColor();
        sf::Vector3f prevColorHsv = RGBtoHSV(prevColor);
        prevColorHsv.x += 5.f;
        m_body[index].SetColor(HSVtoRGB(prevColorHsv));
    }   
}

void Snake::update()
{
    if (m_body.empty() == false && m_dir != None && m_alive == true)
    {
        move();
        checkCollision();
    }
}

void Snake::move()
{
    if (m_dir == Direction::None) return;

    if (m_dir == Direction::Left && m_body[0].GetPosition().x <= 0) 
        m_alive = false;
    else if (m_dir == Direction::Right && m_body[0].GetPosition().x >= m_cells_number.x - 1) 
        m_alive = false;
    else if (m_dir == Direction::Up && m_body[0].GetPosition().y <= 0) 
        m_alive = false;
    else if (m_dir == Direction::Down && m_body[0].GetPosition().y >= m_cells_number.y - 1) 
        m_alive = false;

    if (m_alive == true)
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
}

void Snake::checkCollision()
{
    if (m_body.size() >= 5 && m_alive == true)
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
                if (tail_pos.y == m_cells_number.y - 1)
                {
                    if (tail_pos.x + 1 <= m_cells_number.x - 1)
                        m_body.push_back(DataCell(tail_pos.x + 1, tail_pos.y));
                    else 
                        m_body.push_back(DataCell(tail_pos.x - 1, tail_pos.y));
                }
                else 
                    m_body.push_back(DataCell(tail_pos.x, tail_pos.y + 1));
            }
            else
            {
                if (tail_pos.y == 0)
                {
                    if (tail_pos.x + 1 <= m_cells_number.x - 1)
                        m_body.push_back(DataCell(tail_pos.x + 1, tail_pos.y));
                    else
                        m_body.push_back(DataCell(tail_pos.x - 1, tail_pos.y));
                }
                else
                    m_body.push_back(DataCell(tail_pos.x, tail_pos.y - 1));
            }
        }
        else if (tail_pos.y == pre_tail_pos.y)
        {
            if (tail_pos.x > pre_tail_pos.x)
            {
                if (tail_pos.x == m_cells_number.x - 1)
                {
                    if (tail_pos.y + 1 <= m_cells_number.y - 1)
                        m_body.push_back(DataCell(tail_pos.x, tail_pos.y + 1));
                    else
                        m_body.push_back(DataCell(tail_pos.x, tail_pos.y - 1));
                }
                else 
                    m_body.push_back(DataCell(tail_pos.x + 1, tail_pos.y));
            }
            else
            {
                if (tail_pos.x == 0)
                {
                    if (tail_pos.y + 1 <= m_cells_number.y - 1)
                        m_body.push_back(DataCell(tail_pos.x, tail_pos.y + 1));
                    else
                        m_body.push_back(DataCell(tail_pos.x, tail_pos.y - 1));
                }
                else
                    m_body.push_back(DataCell(tail_pos.x - 1, tail_pos.y));
            }
        }
    }
    else 
    {
        if (m_dir == Direction::Down)
            m_body.push_back(DataCell(tail_pos.x, tail_pos.y - 1));
        else if (m_dir == Direction::Up)    
            m_body.push_back(DataCell(tail_pos.x, tail_pos.y + 1));
        else if (m_dir == Direction::Left)   
            m_body.push_back(DataCell(tail_pos.x + 1, tail_pos.y));
        else if (m_dir == Direction::Right) 
            m_body.push_back(DataCell(tail_pos.x - 1, tail_pos.y));
    }
    UpdateColor(m_body.size() - 1);
}

void Snake::ProcessInput(const sf::Keyboard::Key& key) 
{
    if ((key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::A) && CanMove(Direction::Left) == true) SetDirection(Direction::Left);
    else if ((key == sf::Keyboard::Key::Right || key == sf::Keyboard::Key::D) && CanMove(Direction::Right) == true) SetDirection(Direction::Right);
    else if ((key == sf::Keyboard::Up || key == sf::Keyboard::Key::W) && CanMove(Direction::Up) == true) SetDirection(Direction::Up);
    else if ((key == sf::Keyboard::Key::Down || key == sf::Keyboard::Key::S) && CanMove(Direction::Down) == true) SetDirection(Direction::Down);
}

bool Snake::CanMove(Direction dir)
{
    if (m_body.size() == 1)
        return true;

    const sf::Vector2i& head = m_body[0].GetPosition();
    const sf::Vector2i& pre_head = m_body[1].GetPosition();

    if (dir == Direction::Up)
    {
        if (!(head.y > pre_head.y))
            return true;
    }
    else if (dir == Direction::Down)
    {
        if (!(head.y < pre_head.y))
            return true;
    }
    else if (dir == Direction::Left)
    {
        if (!(head.x > pre_head.x))
            return true;
    }
    else if (dir == Direction::Right)
    {  
        if (!(head.x < pre_head.x))
            return true;
    }
    return false;
}

void Snake::MoveBackward()
{
    sf::Vector2i lastPosition;
    if (m_body[0].GetPosition().x < 0)
        lastPosition = {1, 0};
    else if (m_body[0].GetPosition().x >= m_cells_number.x)
        lastPosition = {-1, 0};
    else if (m_body[0].GetPosition().y < 0)
        lastPosition = {0, 1};
    else if (m_body[0].GetPosition().y >= m_cells_number.y)
        lastPosition = {0, -1};
    
    for (int i = 0; i + 1 < m_body.size(); i++)
    {
        m_body[i].SetPosition(m_body[i + 1].GetPosition());
    }
    m_body[m_body.size() - 1].AddPosition(lastPosition);
}

bool Snake::FindPositionInSnake(sf::Vector2i position)
{
    auto it = std::find(m_body.begin(), m_body.end(), position);
    return it != m_body.end();
}

int Snake::getScores()
{
    return m_body.size() - 1;
}