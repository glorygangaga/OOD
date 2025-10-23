#include "include/shapes/SFML/SfmlCircle.hpp"

SfmlCircle::SfmlCircle(const sf::Vector2f &center, const double radius)
{
  m_shape = std::make_shared<sf::CircleShape>();
  m_shape->setRadius(radius);
  m_shape->setPosition(center);
  ApplyStyle();
}
