#include "Game.h"
#include "NumberGenerator.h"
#include "ResourceHolder.h"
#include "ConfigLoader.h"

int main()
{ 
    // Maybe ResourceHolders and ConfigLoader shouldn't be pointers like NumberGenerator
    ResourceHolders::ShaderHolder = new ResourceHolders::ResourceHolder<sf::Shader, std::string>();
    ResourceHolders::FontHolder = new ResourceHolders::ResourceHolder<sf::Font, std::string>();
    
    ResourceHolders::ShaderHolder->load<sf::Shader::Type>("World", "shaders/CellShader.frag", sf::Shader::Fragment);
    ResourceHolders::ShaderHolder->load<sf::Shader::Type>("SnakeEffect", "shaders/SnakeEffect.frag", sf::Shader::Fragment);
    ResourceHolders::FontHolder->load("MainMenuFont", "fonts/Clancy-Free-BF648d4e44231d4.otf");

    ConfigLoader::Config = new ConfigLoader::Loader();
    ConfigLoader::Config->load("config.ini");

    NumberGenerator::init();

    Game game;
    game.run();

    delete ResourceHolders::ShaderHolder;
    delete ResourceHolders::FontHolder;
    delete ConfigLoader::Config;

    return EXIT_SUCCESS;
}