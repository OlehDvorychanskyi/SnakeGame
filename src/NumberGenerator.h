#pragma once 
#include <random>
#include <SFML/Graphics.hpp>

class NumberGenerator
{
private:
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution;
public: 
    NumberGenerator(const int& min, const int& max);
    int generateNumber();
    sf::Vector2i generatePosition(); 
};