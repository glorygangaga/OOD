#include "include/ui/button/Button.hpp"

Button::Button(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::String &textString, const sf::Font &font, const Action &action)
{
  m_action = action;
  m_shape.setPosition(pos);
  m_shape.setSize(size);
  m_shape.setFillColor(sf::Color::White);

  m_text.setFillColor(sf::Color::Black);
  m_text.setString(textString);
  m_text.setCharacterSize(16);
  m_text.setFont(font);

  sf::FloatRect tb = m_text.getGlobalBounds();
  m_text.setOrigin(tb.left + tb.width / 2.0f, tb.top + tb.height / 2.0f);
  m_text.setPosition(pos + size / 2.0f);
}

void Button::Draw(sf::RenderWindow &window) const
{
  window.draw(m_shape);
  window.draw(m_text);
}

bool Button::IsMouseOver(const sf::RenderWindow &window) const
{
  const sf::Vector2i mouse = sf::Mouse::getPosition(window);
  const sf::Vector2f pos = m_shape.getPosition();
  const sf::Vector2f size = m_shape.getSize();

  return mouse.x >= pos.x && mouse.y >= pos.y && mouse.x <= pos.x + size.x && mouse.y <= pos.y + size.y;
}

bool Button::IsClicked(const sf::RenderWindow &window, const sf::Event &event) const
{
  return IsMouseOver(window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left;
}

Action Button::GetAction() const
{
  return m_action;
}