#include "MainMenu.h"
#include <ResourceHolder.h>
#include <PositionManager.h>

MainMenu::MainMenu()
{
    m_shader = &ResourceHolders::ShaderHolder->get("SnakeEffect");
    m_font = &ResourceHolders::FontHolder->get("MainMenuFont");

    sf::Vector2f percentageSize(30.f, 10.f);
    sf::Vector2f buttonPixelSize = PositionManager::percentToPixel(percentageSize);

    float spacePercentage = percentageSize.y + 1.f;

    sf::Vector2f startButtonPosition = PositionManager::percentToPixel({50.f - (percentageSize.x / 2.f), 50.f - (percentageSize.y / 2.f)});
    sf::Vector2f exitButtonPosition = PositionManager::percentToPixel({50.f - (percentageSize.x / 2.f), 50.f - (percentageSize.y / 2.f) + spacePercentage});

    m_buttonStates["Start"] = std::make_pair(Button(startButtonPosition, buttonPixelSize, m_shader, &(*m_font), "START"), false);
    m_buttonStates["Exit"] = std::make_pair(Button(exitButtonPosition, buttonPixelSize, m_shader, &(*m_font), "EXIT"), false);
}

void MainMenu::update(const float& time)
{   
    m_shader->setUniform("u_time", time);
}

void MainMenu::processInput(const sf::Event& event)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f mousePosition = PositionManager::getMousePosition();
        for (auto& button : m_buttonStates)
        {
            if (button.second.first.isInside(mousePosition) == true)
            {
                button.second.second = true;
            }
        }
    }
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    for (const auto& button : m_buttonStates)   
        target.draw(button.second.first, &(*m_shader));        
}

bool MainMenu::isButtonPressed(const std::string& buttonName)
{
    if (m_buttonStates[buttonName].second == true)
    {
        m_buttonStates[buttonName].second = false;
        return true;
    }
    return false;
}