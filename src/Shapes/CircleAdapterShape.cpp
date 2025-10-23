#include "include/shapes/CircleAdapterShape.hpp"

CircleAdapterShape::CircleAdapterShape(const sf::Vector2f &center, const double radius)
    : m_radius(radius), m_circle(center, radius) {};

double CircleAdapterShape::GetArea() const
{
  return M_PI * std::pow(GetRadius(), mathConstants::CIRCLE_VALUE);
}

double CircleAdapterShape::GetPerimeter() const
{
  return mathConstants::CIRCLE_VALUE * M_PI * GetRadius();
}

std::string CircleAdapterShape::ToString() const
{
  const std::string perimiter = output::PERIMETER + std::to_string(GetPerimeter());
  const std::string area = output::AREA + std::to_string(GetArea());

  return inputs::CIRCLE + ' ' + perimiter + output::SEPARATOR + area + '\n';
}

std::shared_ptr<sf::Shape> CircleAdapterShape::GetShape() const
{
  return m_circle.GetShape();
}

double CircleAdapterShape::GetRadius() const
{
  return m_radius;
}

bool CircleAdapterShape::Contains(const sf::Vector2f &point) const
{
  auto shape = m_circle.GetShape();
  sf::Vector2f center = shape->getPosition();
  float radius = shape->getGlobalBounds().width / 2.f;
  sf::Vector2f diff = point - center;
  return (diff.x * diff.x + diff.y * diff.y) <= radius * radius;
}

void CircleAdapterShape::Move(const sf::Vector2f &delta)
{
  m_circle.GetShape()->move(delta);
}
