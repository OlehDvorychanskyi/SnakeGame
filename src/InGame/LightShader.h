#pragma once 
#include <SFML/Graphics.hpp>
#include <string>

class LightShader
{
private:
    sf::Shader shader;
public:
    LightShader(const std::string& shaderPath, const sf::Shader::Type& shaderType = sf::Shader::Fragment);
    void SetColor(const std::string& uniformName, const sf::Color& color);
    void SetPosition(const std::string& uniformName, const sf::Vector2f& position);
    const sf::Shader& get() const;
};