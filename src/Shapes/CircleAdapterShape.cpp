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
