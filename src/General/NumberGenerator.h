#pragma once 
#include <random>
#include <SFML/Graphics.hpp>
#include <vector>

class NumberGenerator
{
private:
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution;
public: 
    NumberGenerator();
    int generateNumberInRange(int min, int max);
    sf::Vector2i generatePosition(const std::vector<sf::Vector2i>& validPositions);
};