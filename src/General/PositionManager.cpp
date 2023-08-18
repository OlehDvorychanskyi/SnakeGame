#include "PositionManager.h"

namespace PositionManager
{
    sf::RenderWindow* m_window = nullptr;
    
    void setRenderWindow(sf::RenderWindow* window) {
        m_window = window;
    }
    
    sf::Vector2f toCenterPositionInOpenGL(const sf::Vector2f& position, const sf::Vector2f& size) {
        return {(position.x * size.x) + (size.x / 2.f), m_window->getSize().y - ((position.y * size.y) + (size.y / 2.f))};
    }

    sf::Vector2f toPositionInOpenGL(const sf::Vector2f& position) {
        return {position.x, m_window->getSize().y - position.y};
    }

    sf::Vector2f percentToPixel(const sf::Vector2f& positionInPercentage) {
        return { m_window->getSize().x * positionInPercentage.x / 100.f, m_window->getSize().y * positionInPercentage.y / 100.f };
    }

    sf::Vector2f pixelToPercent(const sf::Vector2f& positionInPixels) {
        return { positionInPixels.x * 100.f / m_window->getSize().x, positionInPixels.y * 100.f / m_window->getSize().y }; 
    }

    sf::Vector2f getCellSize(const sf::Vector2i& cellsNumber) {
        return {(float)m_window->getSize().x / (float)cellsNumber.x, (float)m_window->getSize().y / (float)cellsNumber.y};
    }

    sf::Vector2f getMousePosition() {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*(m_window));
        return {(float)mousePos.x, (float)mousePos.y};
    }
}