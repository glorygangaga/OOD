#include "include/shapes/SFML/SfmlTriangle.hpp"

SfmlTriangle::SfmlTriangle(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3)
{
  m_shape = std::make_shared<sf::ConvexShape>();
  m_shape->setPointCount(3);
  m_shape->setPoint(0, p1);
  m_shape->setPoint(1, p2);
  m_shape->setPoint(2, p3);
  ApplyStyle();
}
