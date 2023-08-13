#pragma once 
#include <random>
#include <SFML/Graphics.hpp>

namespace NumberGenerator 
{
    extern std::default_random_engine engine;

    void init();
    int inRange(int min, int max);
    sf::Vector2i generatePosition(const std::vector<sf::Vector2i>& validPositions);
};