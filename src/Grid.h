#pragma once 
#include <SFML/Graphics.hpp>
#include "DrawableCell.h"
#include "DataCell.h"
#include <vector>

class Grid : public sf::Drawable 
{
private:
    std::vector<std::vector<DrawableCell>> m_grid;
public:
    Grid(const sf::Vector2f cell_size, const int& cells_number);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void clear();
    void update(const std::vector<DataCell>& cells_info);
    void update(const DataCell& cell_info);
};