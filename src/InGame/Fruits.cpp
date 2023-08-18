#include "Fruits.h"
#include <algorithm>
#include "NumberGenerator.h"
#include "PositionManager.h"

void Fruits::generate(int fruitsNumber, std::vector<sf::Vector2i>& validPositions, sf::Vector2f cellSize)
{
    m_fruitsNumber = fruitsNumber;
    sf::Vector2i temp;
    for (int i = 0; i < fruitsNumber && validPositions.size() != 0; i++)
    {
        temp = NumberGenerator::generatePosition(validPositions);
        m_fruits.push_back(DataCell(temp, generateColor()));
        m_shapes.push_back(sf::RectangleShape(cellSize / 2.f));
        m_shapes[i].setFillColor(m_fruits[i].GetColor());
        m_shapes[i].setPosition({m_fruits[i].GetFloatPosition().x * cellSize.x + (m_shapes[i].getSize().x / 2.f), m_fruits[i].GetFloatPosition().y * cellSize.y + (m_shapes[i].getSize().y / 2.f)});
        
        // delete position from validPositions
        auto it = std::find(validPositions.begin(), validPositions.end(), temp);
        validPositions.erase(it);
    }
}

sf::Color Fruits::generateColor()
{
    int index = NumberGenerator::inRange(0, m_fruitsColors.size() - 1);
    return m_fruitsColors[index];
}

void Fruits::checkFruitsNumber(std::vector<sf::Vector2i>& validPositions, sf::Vector2f cellSize)
{
    if (validPositions.size() != 0 && m_fruits.size() < m_fruitsNumber)
    {
        int size;
        if (m_fruitsNumber - m_fruits.size() <= validPositions.size())
            size = m_fruitsNumber;
        else 
            size = m_fruits.size() + validPositions.size();

        sf::Vector2i temp;
        for (int i = m_fruits.size(); i < size; i++)
        {
            temp = NumberGenerator::generatePosition(validPositions);
            m_fruits.push_back(DataCell(temp, generateColor()));
            m_shapes.push_back(sf::RectangleShape(cellSize / 2.f));
            
            // delete position from validPositions
            auto it = std::find(validPositions.begin(), validPositions.end(), temp);
            validPositions.erase(it);
        }
    }
}

void Fruits::respawnSingle(const sf::Vector2i& CurrentPosition, const sf::Vector2i& NewPosition)
{
    if (NewPosition == sf::Vector2i(-1, -1))
    {
        for (int i = 0; i < m_fruits.size(); i++)
        {
            if (m_fruits[i] == CurrentPosition)
            {
                m_fruits.erase(m_fruits.begin() + i);
                m_shapes.erase(m_shapes.begin() + i);
            }
        }
    }
    else
    {
        auto it = std::find(m_fruits.begin(), m_fruits.end(), CurrentPosition);
        if (it != m_fruits.end())
        {
            it->SetPosition(NewPosition);
            it->SetColor(generateColor());
        }
    }
}

void Fruits::updateShapes(const sf::Vector2f& cellSize)
{
    for (int i = 0; i < m_fruits.size(); i++)
    {
        m_shapes[i].setFillColor(m_fruits[i].GetColor());
        m_shapes[i].setPosition({m_fruits[i].GetFloatPosition().x * cellSize.x + (m_shapes[i].getSize().x / 2.f), m_fruits[i].GetFloatPosition().y * cellSize.y + (m_shapes[i].getSize().y / 2.f)});
    }
}

sf::Vector2i Fruits::checkCollision(const sf::Vector2i& position)
{
    auto it = std::find(m_fruits.begin(), m_fruits.end(), position);
    if (it != m_fruits.end())
        return it->GetPosition();
    return {-1, -1};
}

void Fruits::setLightColorArray(sf::Shader* shader)
{
    std::vector<sf::Vector3f> lightColors;
    sf::Color tempColor;
    for (unsigned int i = 0; i < m_fruits.size(); i++)
    {
        tempColor = m_fruits[i].GetColor();
        lightColors.push_back({ (float)tempColor.r, (float)tempColor.g, (float)tempColor.b });
    }
    shader->setUniformArray("fruitLightColors", &lightColors[0], lightColors.size()); 
    shader->setUniform("currentSize",  (int)m_fruits.size()); 
}

void Fruits::setLightPositionArray(sf::Shader* shader, const sf::Vector2f& cellSize)
{
    std::vector<sf::Vector2f> lightPositions;
    for (unsigned int i = 0; i < m_fruits.size(); i++)
    {
        lightPositions.push_back(PositionManager::toCenterPositionInOpenGL(m_fruits[i].GetFloatPosition(), cellSize));
    }
    shader->setUniformArray("fruitLightPositions", &lightPositions[0], lightPositions.size()); 
    shader->setUniform("currentSize",  (int)m_fruits.size()); 
}

void Fruits::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < m_shapes.size(); i++)
        target.draw(m_shapes[i], states);
}

void Fruits::reset()
{
    m_fruits.clear();
    m_shapes.clear();
}   