#include "LightShader.h"
#include <iostream>

LightShader::LightShader(const std::string& shaderPath, const sf::Shader::Type& shaderType)
{
    if (!shader.loadFromFile(shaderPath, shaderType))
        std::cout << "ERROR::LIGHTSHADER Couldn't open shader file" << std::endl;
    else 
        std::cout << "Light shader load correctly" << std::endl;
}

void LightShader::SetColor(const std::string& uniformName, const sf::Color& color)
{
    shader.setUniform(uniformName, sf::Vector3f(color.r, color.g, color.b));
}

void LightShader::SetPosition(const std::string& uniformName, const sf::Vector2f& position)
{
    shader.setUniform(uniformName, position);
}

const sf::Shader& LightShader::get() const
{
    return shader;
}