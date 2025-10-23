#include "include/shapes/SFML/SfmlRectangle.hpp"

SfmlRectangle::SfmlRectangle(const sf::Vector2f &p1, const sf::Vector2f &p2)
{
  const float width = std::abs(p2.x - p1.x);
  const float height = std::abs(p2.y - p1.y);

  m_shape = std::make_shared<sf::RectangleShape>();

  m_shape->setSize({static_cast<float>(width), static_cast<float>(height)});
  m_shape->setPosition(p1);
  ApplyStyle();
}
