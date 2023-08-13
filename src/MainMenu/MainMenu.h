#pragma once
#include <SFML/Graphics.hpp>
#include <Button.h>
#include <vector>
#include <map>

class MainMenu : public sf::Drawable
{
private:
    sf::Shader* m_shader;
    sf::Font* m_font;
    
    std::map<std::string, std::pair<Button, bool>> m_buttonStates;
public:
    MainMenu();
    
    void update(const float& time);
    void processInput(const sf::Event& event);
    bool isButtonPressed(const std::string& buttonName);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};