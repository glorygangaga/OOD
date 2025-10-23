#include "include/shapes/RectangleAdapterShape.hpp"

RectangleAdapterShape::RectangleAdapterShape(const sf::Vector2f &p1, const sf::Vector2f &p2) : m_rectangle(p1, p2)
{
  m_width = std::abs(p2.x - p1.x);
  m_height = std::abs(p2.y - p1.y);
};

double RectangleAdapterShape::GetArea() const
{
  return GetWidth() * GetHeight();
}
double RectangleAdapterShape::GetPerimeter() const
{
  return 2 * (GetWidth() + GetHeight());
}

std::string RectangleAdapterShape::ToString() const
{
  const std::string perimiter = output::PERIMETER + std::to_string(GetPerimeter());
  const std::string area = output::AREA + std::to_string(GetArea());

  return inputs::RECT + ' ' + perimiter + output::SEPARATOR + area + '\n';
}

std::shared_ptr<sf::Shape> RectangleAdapterShape::GetShape() const
{
  return m_rectangle.GetShape();
}

bool RectangleAdapterShape::Contains(const sf::Vector2f &point) const
{
  return m_rectangle.GetShape()->getGlobalBounds().contains(point);
}

void RectangleAdapterShape::Move(const sf::Vector2f &delta)
{
  m_rectangle.GetShape()->move(delta);
}

double RectangleAdapterShape::GetWidth() const
{
  return m_width;
}

double RectangleAdapterShape::GetHeight() const
{
  return m_height;
}
