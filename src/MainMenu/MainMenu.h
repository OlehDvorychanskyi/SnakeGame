#pragma once
#include <SFML/Graphics.hpp>
#include <PositionManager.h>
#include <ShaderManager.h>
#include <Button.h>
#include <vector>
#include <map>

class MainMenu : public sf::Drawable
{
private:
    PositionManager* m_positionManager;
    ShaderManager* m_shaderManager;
    FontManager* m_fontManager;

    sf::Shader* m_shader;
    sf::Font* m_font;
    
    std::map<std::string, std::pair<Button, bool>> m_buttonStates;
public:
    MainMenu(PositionManager* converterPtr, ShaderManager* shaderManagerPtr, FontManager* fontManagerPtr);
    
    void update(const float& time);
    void processInput(const sf::Event& event);
    bool isButtonPressed(const std::string& buttonName);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};