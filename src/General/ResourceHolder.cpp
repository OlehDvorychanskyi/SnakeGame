#include "ResourceHolder.h"

namespace ResourceHolders
{
    ResourceHolder<sf::Shader, std::string>* ShaderHolder = nullptr;
    ResourceHolder<sf::Font, std::string>* FontHolder = nullptr;   
};