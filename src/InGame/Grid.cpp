#include "Grid.h"

Grid::Grid(const sf::Vector2f cell_size, const sf::Vector2i& cells_number)
{
    for (int i = 0; i < cells_number.x; i++)
    {
        std::vector<DrawableCell> row;
        for (int j = 0; j < cells_number.y; j++)
        {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
            {
                row.push_back(DrawableCell(cell_size, i, j, sf::Color::Black));
            }
            else 
            {
                row.push_back(DrawableCell(cell_size, i, j, sf::Color(25, 25, 25)));
            }
        }
        m_grid.push_back(row);
    }
}

void Grid::resize(const sf::Vector2f cell_size, const int& cells_number)
{
    for (int i = 0; i < cells_number; i++)
    {
        for (int j = 0; j < cells_number; j++)
        {
            m_grid[i][j].SetSize(cell_size);
        }
    }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < m_grid.size(); i++)
    {
        for (int j = 0; j < m_grid[i].size(); j++)
        {
            if (m_grid[i][j].GetColor() == sf::Color(25, 25, 25))
            {
                target.draw(m_grid[i][j], states);
            }
            else 
            {
                target.draw(m_grid[i][j]);
            }
        }
    }
}

void Grid::clear()
{
    for (int i = 0; i < m_grid.size(); i++)
    {
        for (int j = 0; j < m_grid[i].size(); j++)
        {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))  
                m_grid[i][j].SetColor(sf::Color::Black);
            else
                m_grid[i][j].SetColor(sf::Color(25, 25, 25));
        }
    }
}

void Grid::update(const std::vector<DataCell>& cells_info)
{
    for (int i = 0; i < cells_info.size(); i++)
    {
        m_grid[cells_info[i].GetPosition().x][cells_info[i].GetPosition().y].SetColor(cells_info[i].GetColor());
    }
}

void Grid::update(const DataCell& cell_info)
{
    m_grid[cell_info.GetPosition().x][cell_info.GetPosition().y].SetColor(cell_info.GetColor());
}