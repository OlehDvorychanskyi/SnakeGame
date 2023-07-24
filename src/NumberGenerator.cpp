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