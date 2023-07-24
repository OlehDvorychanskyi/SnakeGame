#pragma once 
#include <random>

class NumberGenerator
{
private:
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution;
public: 
    NumberGenerator(const int& min, const int& max);
    int generateNumber();
};