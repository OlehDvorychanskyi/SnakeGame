#include "NumberGenerator.h"

NumberGenerator::NumberGenerator(const int& min, const int& max)
    : distribution(min, max)
{
    std::random_device rd;
    engine.seed(rd());
}

int NumberGenerator::generateNumber()
{
    return distribution(engine);
}

int NumberGenerator::generateNumberInRange(int min, int max) 
{
    std::uniform_int_distribution<int> rangeDistribution(min, max);
    return rangeDistribution(engine);
}

sf::Vector2i NumberGenerator::generatePosition() // Bug here: endless loop
{
    int x = generateNumber();
    int y = generateNumber();
    return sf::Vector2i(x, y);
}

sf::Vector2i NumberGenerator::generatePosition(const std::vector<sf::Vector2i>& validPositions)
{
    return validPositions[generateNumberInRange(0, validPositions.size() - 1)];
}