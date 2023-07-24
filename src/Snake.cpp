#include "Snake.h"

Snake::Snake(sf::Vector2f segment_size)
    : m_segment_size{segment_size}
{
    reset();
}

void Snake::reset()
{
    m_body.clear();

    m_body.push_back(Cell(m_segment_size, 5, 5));
    m_body.push_back(Cell(m_segment_size, 5, 6));
    m_body.push_back(Cell(m_segment_size, 5, 7));

    for (int i = 0; i < m_body.size(); i++)
    {
        if (i == 0)
        {
            m_body[i].SetColor(sf::Color::Yellow);
        }
        else
        {
            m_body[i].SetColor(sf::Color::Green);
        }
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
        m_body[i].SetPosition(m_body[i - 1].GetPositionPX());
    }

    if (m_dir == Direction::Left) m_body[0].AddPosition(-1, 0);
    else if (m_dir == Direction::Right) m_body[0].AddPosition(1, 0);
    else if (m_dir == Direction::Up) m_body[0].AddPosition(0, -1);
    else if (m_dir == Direction::Down) m_body[0].AddPosition(0, 1);
}

void Snake::grow()
{  
    if (m_body.empty() == true) return;
    const Cell& tail = m_body[m_body.size() - 1];
    sf::Vector2i tail_pos = tail.GetPositionXY();
    if (m_body.size() > 1)
    {
        const Cell& pre_tail = m_body[m_body.size() - 2];
        sf::Vector2i pre_tail_pos = pre_tail.GetPositionXY();
        if (tail_pos.x == pre_tail_pos.x)
        {
            if (tail_pos.y > pre_tail_pos.y)    
            {
                m_body.push_back(Cell(m_segment_size, tail_pos.x, tail_pos.y + 1));
            }
            else
            {
                m_body.push_back(Cell(m_segment_size, tail_pos.x, tail_pos.y - 1));
            }
        }
        else if (tail_pos.y == pre_tail_pos.y)
        {
            if (tail_pos.x > pre_tail_pos.x)
            {
                m_body.push_back(Cell(m_segment_size, tail_pos.x + 1, tail_pos.y));
            }
            else
            {
                m_body.push_back(Cell(m_segment_size, tail_pos.x - 1, tail_pos.y));
            }
        }
    }
    else 
    {
        if (m_dir == Direction::Down)   m_body.push_back(Cell(m_segment_size, tail_pos.x, tail_pos.y - 1));
        else if (m_dir == Direction::Up)    m_body.push_back(Cell(m_segment_size, tail_pos.x, tail_pos.y + 1));
        else if (m_dir == Direction::Left)    m_body.push_back(Cell(m_segment_size, tail_pos.x + 1, tail_pos.y));
        else if (m_dir == Direction::Right)    m_body.push_back(Cell(m_segment_size, tail_pos.x - 1, tail_pos.y));
    }
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_body.empty() == false)
    {
        for (int i = 0; i < m_body.size(); i++)
        {
            target.draw(m_body[i].GetRectangleShape(), states);
        }
    }
}

void Snake::ProcessInput(const sf::Keyboard::Key& key)
{
    if (key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::A) SetDirection(Direction::Left);
    else if (key == sf::Keyboard::Key::Right || key == sf::Keyboard::Key::D) SetDirection(Direction::Right);
    else if (key == sf::Keyboard::Up || key == sf::Keyboard::Key::W) SetDirection(Direction::Up);
    else if (key == sf::Keyboard::Key::Down || key == sf::Keyboard::Key::S) SetDirection(Direction::Down);
}