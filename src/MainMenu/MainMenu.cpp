#include "MainMenu.h"


MainMenu::MainMenu(PositionManager* converterPtr, ShaderManager* shaderManagerPtr, FontManager* fontManagerPtr)
{
    m_positionManager = converterPtr;
    m_shaderManager = shaderManagerPtr;
    m_fontManager = fontManagerPtr;

    m_shader = &m_shaderManager->get("SnakeEffect");
    m_font = &m_fontManager->get("MainMenuFont");

    sf::Vector2f percentageSize(30.f, 10.f);
    sf::Vector2f buttonPixelSize = m_positionManager->percentToPixel(percentageSize);

    float spacePercentage = percentageSize.y + 1.f;

    sf::Vector2f startButtonPosition = m_positionManager->percentToPixel({50.f - (percentageSize.x / 2.f), 50.f - (percentageSize.y / 2.f)});
    sf::Vector2f exitButtonPosition = m_positionManager->percentToPixel({50.f - (percentageSize.x / 2.f), 50.f - (percentageSize.y / 2.f) + spacePercentage});

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
        sf::Vector2f mousePosition = m_positionManager->getMousePosition();
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