#include "GameOverScreen.h"
#include "PositionManager.h"
#include <ResourceHolder.h>

GameOverScreen::GameOverScreen(int scores)
    : m_text{"GAME OVER", ResourceHolders::FontHolder->get("MainMenuFont")}, 
    m_restart{"Press space to restart", ResourceHolders::FontHolder->get("MainMenuFont")},
    m_scoresText("Scores: " + std::to_string(scores), ResourceHolders::FontHolder->get("MainMenuFont"))
{   
    darkBackground.setSize({PositionManager::m_window->getSize().x, PositionManager::m_window->getSize().y});
    darkBackground.setFillColor(sf::Color(0, 0, 0, 150));

    m_text.setOrigin(m_text.getGlobalBounds().getSize() / 2.f + m_text.getLocalBounds().getPosition());
    m_text.setPosition(darkBackground.getPosition() + (darkBackground.getSize() / 2.f));

    m_scoresText.setOrigin(m_scoresText.getGlobalBounds().getSize() / 2.f + m_scoresText.getLocalBounds().getPosition());
    m_scoresText.setPosition(darkBackground.getPosition().x + (darkBackground.getSize().x / 2.f), darkBackground.getPosition().y + (darkBackground.getSize().y / 2.f) + PositionManager::percentToPixel({0, 5}).y);

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