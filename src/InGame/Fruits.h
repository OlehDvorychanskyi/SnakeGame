#pragma once 
#include "DataCell.h"
#include "SFML/Graphics.hpp"

typedef DataCell Fruit;

class Fruits : public sf::Drawable
{
private:
    unsigned int m_fruitsNumber;
    std::vector<Fruit> m_fruits;
    std::vector<sf::Color> m_fruitsColors = { sf::Color::Red, sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta };
    std::vector<sf::RectangleShape> m_shapes; // this is for drawing fruits that has size = cellSize / 2;
public:
    void reset();
    void respawnSingle(const sf::Vector2i& CurrentPosition, const sf::Vector2i& NewPosition);
    void generate(int fruitsNumber, std::vector<sf::Vector2i>& validPositions, sf::Vector2f cellSize);

    sf::Vector2i checkCollision(const sf::Vector2i& position);
    
    void setLightColorArray(sf::Shader* shader);
    void setLightPositionArray(sf::Shader* shader, const sf::Vector2f& cellSize);

    std::vector<Fruit>& GetBody() { return m_fruits; }

    void updateShapes(const sf::Vector2f& cellSize);
    sf::Color generateColor();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void checkFruitsNumber(std::vector<sf::Vector2i>& validPositions, sf::Vector2f cellSize);
};