#pragma once 
#include <SFML/Graphics.hpp>
#include "DrawableCell.h"
#include "DataCell.h"
#include <vector>

class Grid : public sf::Drawable 
{
    const sf::Color Grey = sf::Color(10, 10, 10); // Dosn't effect to color because color is set in shader
private:
    std::vector<std::vector<DrawableCell>> m_grid;
public:
    Grid(const sf::Vector2f cell_size, const sf::Vector2i& cells_number);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void clear();
    void update(const std::vector<DataCell>& cells_info);
    void update(const DataCell& cell_info);

    void resize(const sf::Vector2f cell_size, const int& cells_number);
};