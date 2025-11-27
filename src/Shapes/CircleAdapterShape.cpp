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

ShapeMemento CircleAdapterShape::SaveState() const
{
  ShapeMemento state;
  const std::shared_ptr<sf::Shape> s = m_circle.GetShape();

  state.SetFillColor(s->getFillColor());
  state.SetOutlineColor(s->getOutlineColor());
  state.SetThickness(s->getOutlineThickness());
  state.SetTransform(s->getTransform());

  return state;
}

void CircleAdapterShape::RestoreState(const ShapeMemento &lastState)
{
  const std::shared_ptr<sf::Shape> s = m_circle.GetShape();

  s->setFillColor(lastState.GetFillColor());
  s->setOutlineColor(lastState.GetOutlineColor());
  s->setOutlineThickness(lastState.GetThickness());

  sf::Vector2f pos = lastState.GetTransform().transformPoint({0.f, 0.f});
  s->setPosition(pos);
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
