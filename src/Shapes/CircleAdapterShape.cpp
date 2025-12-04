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

double CircleAdapterShape::GetRadius() const
{
  return m_radius;
}

bool CircleAdapterShape::Contains(const sf::Vector2f &point) const
{
  return GetShape()->getGlobalBounds().contains(point);
}

void CircleAdapterShape::Move(const sf::Vector2f &delta)
{
  m_circle.GetShape()->move(delta);
}

size_t CircleAdapterShape::GetStateSize() const
{
  return 1;
}
