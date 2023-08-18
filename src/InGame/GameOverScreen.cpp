#include "GameOverScreen.h"
#include "PositionManager.h"
#include <ResourceHolder.h>

GameOverScreen::GameOverScreen()
    : m_text{"GAME OVER", ResourceHolders::FontHolder->get("MainMenuFont")}, 
    m_restart{"Space to Retry | Esc for Menu", ResourceHolders::FontHolder->get("MainMenuFont")}
{   
    darkBackground.setSize({PositionManager::m_window->getSize().x, PositionManager::m_window->getSize().y});
    darkBackground.setFillColor(sf::Color(0, 0, 0, 150));

    m_text.setCharacterSize(50);
    m_text.setOrigin(m_text.getGlobalBounds().getSize() / 2.f + m_text.getLocalBounds().getPosition());
    m_text.setPosition(darkBackground.getPosition() + (darkBackground.getSize() / 2.f));

    m_scoresText.setFont(ResourceHolders::FontHolder->get("MainMenuFont"));

    m_restart.setOrigin(m_restart.getGlobalBounds().getSize() / 2.f + m_restart.getLocalBounds().getPosition());
    m_restart.setPosition(darkBackground.getPosition().x + (darkBackground.getSize().x / 2.f), darkBackground.getPosition().y + (darkBackground.getSize().y / 2.f) + PositionManager::percentToPixel({0, 10}).y);
}

void GameOverScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(darkBackground, states);
    target.draw(m_text, states);
    target.draw(m_scoresText, states);
    target.draw(m_restart, states);
}