#include "Fruits.h"
#include <algorithm>
#include "NumberGenerator.h"
#include "PositionManager.h"

void Fruits::spawn(const int& fruitsNumber, const std::vector<sf::Vector2i>& validPositions, const sf::Vector2f& cellSize)
{
    for (int i = 0; i < fruitsNumber; i++)
    {
        m_fruits.push_back(DataCell(NumberGenerator::generatePosition(validPositions), generateColor()));
        m_shapes.push_back(sf::RectangleShape(cellSize / 2.f));
        m_shapes[i].setFillColor(m_fruits[i].GetColor());
        m_shapes[i].setPosition({m_fruits[i].GetFloatPosition().x * cellSize.x + (m_shapes[i].getSize().x / 2.f), m_fruits[i].GetFloatPosition().y * cellSize.y + (m_shapes[i].getSize().y / 2.f)});
    }
}

sf::Color Fruits::generateColor()
{
    int index = NumberGenerator::inRange(0, m_fruitsColors.size() - 1);
    return m_fruitsColors[index];
}

void Fruits::respawnAll(const std::vector<sf::Vector2i>& validPositions)
{
    for (int i = 0; i < m_fruits.size(); i++)
    {
        m_fruits[i].SetPosition(NumberGenerator::generatePosition(validPositions));
        m_fruits[i].SetColor(generateColor());
    }
}

void Fruits::respawnSingle(const sf::Vector2i& CurrentPosition, const sf::Vector2i& NewPosition)
{
    auto it = std::find(m_fruits.begin(), m_fruits.end(), CurrentPosition);
    if (it != m_fruits.end())
    {
        it->SetPosition(NewPosition);
        it->SetColor(generateColor());
    }
}

void Fruits::updateShapes(const sf::Vector2f& cellSize)
{
    for (int i = 0; i < m_shapes.size(); i++)
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

void Fruits::setLightArray(sf::Shader* shader, const sf::Vector2f& cellSize) // should change because l don't need this to update every frame
{
    constexpr int fruitsNumber = 5;
    sf::Vector2f lightPositions[fruitsNumber];
    sf::Vector3f lightColors[fruitsNumber];

    sf::Color tempColor;
    for (int i = 0; i < fruitsNumber; i++)
    {
        lightPositions[i] = PositionManager::toCenterPositionInOpenGL(m_fruits[i].GetFloatPosition(), cellSize);
        tempColor = m_fruits[i].GetColor();
        lightColors[i] = { tempColor.r, tempColor.g, tempColor.b };
    }

    shader->setUniformArray("fruitLightPositions", lightPositions, fruitsNumber);
    shader->setUniformArray("fruitLightColors", lightColors, fruitsNumber);   
}

void Fruits::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < m_shapes.size(); i++)
        target.draw(m_shapes[i], states);
}