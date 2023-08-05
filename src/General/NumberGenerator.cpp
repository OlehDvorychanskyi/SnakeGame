#include "NumberGenerator.h"

NumberGenerator::NumberGenerator()
{
    std::random_device rd;
    engine.seed(rd());
}

int NumberGenerator::generateNumberInRange(int min, int max) 
{
    std::uniform_int_distribution<int> rangeDistribution(min, max);
    return rangeDistribution(engine);
}

sf::Vector2i NumberGenerator::generatePosition(const std::vector<sf::Vector2i>& validPositions)
{
    return validPositions[generateNumberInRange(0, validPositions.size() - 1)];
}