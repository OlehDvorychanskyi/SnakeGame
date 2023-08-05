#include "Button.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, sf::Shader* buttonShader, sf::Font* font, const std::string buttonTitle)
    : m_text(buttonTitle, *font)
{
    m_button.setPosition(position);
    m_button.setSize(size);
    m_shader = buttonShader;

    m_text.setOrigin(m_text.getGlobalBounds().getSize() / 2.f + m_text.getLocalBounds().getPosition());
    m_text.setPosition(m_button.getPosition() + (m_button.getSize() / 2.f));
    m_text.setFillColor(sf::Color::White);

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{   
    m_shader->setUniform("rectSize", m_button.getSize());
    m_shader->setUniform("rectPosition", sf::Vector2f(m_button.getPosition().x, target.getSize().y - m_button.getPosition().y));

    target.draw(m_button, &(*m_shader));
    target.draw(m_text);
}

bool Button::isInside(const sf::Vector2f& position) const
{
    sf::Vector2f buttonSize = m_button.getSize();
    sf::Vector2f buttonPosition = m_button.getPosition();
    return (position.x > buttonPosition.x && position.x < buttonPosition.x + buttonSize.x && position.y > buttonPosition.y && position.y < buttonPosition.y + buttonSize.y);
}