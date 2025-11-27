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

void RectangleAdapterShape::Accept(IShapeVisitor &visitor)
{
  visitor.Visit(*this);
}

ShapeMemento RectangleAdapterShape::SaveState() const
{
  ShapeMemento state;
  const std::shared_ptr<sf::Shape> s = m_rectangle.GetShape();

  state.SetFillColor(s->getFillColor());
  state.SetOutlineColor(s->getOutlineColor());
  state.SetThickness(s->getOutlineThickness());
  state.SetTransform(s->getTransform());

  return state;
}

void RectangleAdapterShape::RestoreState(const ShapeMemento &lastState)
{
  const std::shared_ptr<sf::Shape> s = m_rectangle.GetShape();

  s->setFillColor(lastState.GetFillColor());
  s->setOutlineColor(lastState.GetOutlineColor());
  s->setOutlineThickness(lastState.GetThickness());

  sf::Vector2f pos = lastState.GetTransform().transformPoint({0.f, 0.f});
  s->setPosition(pos);
}

double RectangleAdapterShape::GetWidth() const
{
  return m_width;
}

double RectangleAdapterShape::GetHeight() const
{
  return m_height;
}
