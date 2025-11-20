#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "include/Constants.hpp"

class Button
{
public:
  Button(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::String &textString, const sf::Font &font, const Action &action);

  std::function<void()> onClick;
  void Draw(sf::RenderWindow &window) const;
  bool IsMouseOver(const sf::RenderWindow &window) const;
  bool IsClicked(const sf::RenderWindow &window, const sf::Event &event) const;
  Action GetAction() const;

private:
  sf::RectangleShape m_shape;
  sf::Text m_text;
  Action m_action;
};
