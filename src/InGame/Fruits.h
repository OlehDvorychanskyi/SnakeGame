#pragma once 
#include "DataCell.h"
#include "SFML/Graphics.hpp"

typedef DataCell Fruit;

class Fruits : public sf::Drawable
{
private:
    std::vector<Fruit> m_fruits;
    std::vector<sf::Color> m_fruitsColors = { sf::Color::Red, sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta };
    std::vector<sf::RectangleShape> m_shapes; // this is for drawing fruits that has size = cellSize / 2;

    sf::Color generateColor();
public:
    void respawnAll(const std::vector<sf::Vector2i>& validPositions);
    void respawnSingle(const sf::Vector2i& CurrentPosition, const sf::Vector2i& NewPosition);
    void spawn(const int& fruitsNumber, const std::vector<sf::Vector2i>& validPositions, const sf::Vector2f& cellSize);

    sf::Vector2i checkCollision(const sf::Vector2i& position);

    void setLightArray(sf::Shader* shader, const sf::Vector2f& cellSize); // should change

    std::vector<Fruit>& GetBody() { return m_fruits; }

    void updateShapes(const sf::Vector2f& cellSize);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};