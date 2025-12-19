#include "include/shapes/CircleAdapterShape.hpp"

CircleAdapterShape::CircleAdapterShape(const sf::Vector2f &center, const float radius)
    : m_radius(radius), m_center(center), m_circle(center, radius) {};

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

void CircleAdapterShape::Accept(IShapeVisitor &visitor)
{
  visitor.Visit(*this);
}

std::vector<ShapeMemento> CircleAdapterShape::SaveState() const
{
  std::vector<ShapeMemento> states(1);

  const std::shared_ptr<sf::Shape> s = m_circle.GetShape();

  states[0].SetFillColor(s->getFillColor());
  states[0].SetOutlineColor(s->getOutlineColor());
  states[0].SetThickness(s->getOutlineThickness());
  states[0].SetPosition(s->getPosition());

  return states;
}

void CircleAdapterShape::RestoreState(const std::vector<ShapeMemento> &lastState)
{
  const std::shared_ptr<sf::Shape> s = m_circle.GetShape();

  s->setFillColor(lastState[0].GetFillColor());
  s->setOutlineColor(lastState[0].GetOutlineColor());
  s->setOutlineThickness(lastState[0].GetThickness());
  s->setPosition(lastState[0].GetPosition());
}

float CircleAdapterShape::GetRadius() const
{
  return m_radius;
}

bool CircleAdapterShape::Contains(const sf::Vector2f &point) const
{
  return GetShape()->getGlobalBounds().contains(point);
}

void CircleAdapterShape::SerializeToBinary(std::ostream &out) const
{
  const auto shape = m_circle.GetShape();
  SHAPES_TYPE type = SHAPES_TYPE::CIRCLE_T;
  out.write(reinterpret_cast<const char *>(&type), sizeof(type));

  sf::Vector2f pos = shape->getPosition();
  out.write(reinterpret_cast<const char *>(&pos.x), sizeof(pos.x));
  out.write(reinterpret_cast<const char *>(&pos.y), sizeof(pos.y));

  out.write(reinterpret_cast<const char *>(&m_center.x), sizeof(m_center.x));
  out.write(reinterpret_cast<const char *>(&m_center.y), sizeof(m_center.y));

  out.write(reinterpret_cast<const char *>(&m_radius), sizeof(m_radius));

  uint32_t color = shape->getOutlineColor().toInteger();
  out.write(reinterpret_cast<const char *>(&color), sizeof(color));

  float thickness = shape->getOutlineThickness();
  out.write(reinterpret_cast<const char *>(&thickness), sizeof(thickness));

  uint32_t colorFill = shape->getFillColor().toInteger();
  out.write(reinterpret_cast<const char *>(&colorFill), sizeof(colorFill));
}

void CircleAdapterShape::SerializeToText(std::ostream &out) const
{
  const auto shape = m_circle.GetShape();
  out << inputs::CIRCLE << ' ';

  sf::Vector2f pos = shape->getPosition();
  out << pos.x << ' ' << pos.y << ' ' << m_center.x << ' ' << m_center.y << ' ' << m_radius << ' ';

  uint32_t color = shape->getOutlineColor().toInteger();
  float thickness = shape->getOutlineThickness();
  uint32_t colorFill = shape->getFillColor().toInteger();
  out << color << ' ' << thickness << ' ' << colorFill << '\n';
}

void CircleAdapterShape::Move(const sf::Vector2f &delta)
{
  m_circle.GetShape()->move(delta);
}

size_t CircleAdapterShape::GetStateSize() const
{
  return 1;
}
