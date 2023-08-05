#include "DataCell.h"

DataCell::DataCell(const int& x, const int& y, const sf::Color& color)
{
    m_position = sf::Vector2i(x, y);
    m_color = color;
}

DataCell::DataCell(const sf::Vector2i& position, const sf::Color& color)
{
    m_position = position;
    m_color = color;
}

void DataCell::SetColor(const sf::Color& color)
{
    m_color = color;
}

void DataCell::AddColor(const sf::Color& color)
{
    m_color += color;
}

void DataCell::SubtructColor(const sf::Color& color)
{
    m_color -= color;
}

const sf::Color& DataCell::GetColor() const
{
    return m_color;
}

void DataCell::SetPosition(const int& x, const int& y)
{
    m_position = sf::Vector2i(x, y);
}

void DataCell::SetPosition(const sf::Vector2i& position)
{
    m_position = position;
}

void DataCell::AddPosition(const int& x, const int& y)
{
    m_position += sf::Vector2i(x, y);
}

void DataCell::AddPosition(const sf::Vector2i& position)
{
    m_position += position;
}

const sf::Vector2i& DataCell::GetPosition() const
{
    return m_position;
}

sf::Vector2f DataCell::GetFloatPosition() const
{
    return {(float)m_position.x, (float)m_position.y};
}