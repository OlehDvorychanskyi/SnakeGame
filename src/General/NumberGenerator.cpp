#include "NumberGenerator.h"

namespace NumberGenerator 
{
    std::default_random_engine engine;

    void init() 
    {
        engine.seed(std::random_device{}());
    }

    int inRange(int min, int max) 
    {
        std::uniform_int_distribution<int> rangeDistribution(min, max);
        return rangeDistribution(engine);        
    }

    sf::Vector2i generatePosition(const std::vector<sf::Vector2i>& validPositions) 
    {
        if (validPositions.size() != 0)
            return validPositions[inRange(0, validPositions.size() - 1)];
        return {-1, -1};
    }
}