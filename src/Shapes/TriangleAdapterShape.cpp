#include "include/shapes/TriangleAdapterShape.hpp"

TriangleAdapterShape::TriangleAdapterShape(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3)
    : m_p1(p1), m_p2(p2), m_p3(p3), m_triangle(p1, p2, p3) {};

sf::Vector2f TriangleAdapterShape::GetP1() const { return m_p1; };
sf::Vector2f TriangleAdapterShape::GetP2() const { return m_p2; };
sf::Vector2f TriangleAdapterShape::GetP3() const { return m_p3; };

double TriangleAdapterShape::GetArea() const
{
  const double a = GetP1().x * (GetP2().y - GetP3().y);
  const double b = GetP2().x * (GetP3().y - GetP1().y);
  const double c = GetP3().x * (GetP1().y - GetP2().y);
  return std::abs(a + b + c) * 0.5;
}

double TriangleAdapterShape::GetPerimeter() const
{
  const double a = GetLineLength(GetP1(), GetP2()); // "/"
  const double b = GetLineLength(GetP1(), GetP3()); // "\"
  const double c = GetLineLength(GetP2(), GetP3()); // "_"
  return a + b + c;
}

std::string TriangleAdapterShape::ToString() const
{
  const std::string perimiter = output::PERIMETER + std::to_string(GetPerimeter());
  const std::string area = output::AREA + std::to_string(GetArea());

  return inputs::TRIANGLE + ' ' + perimiter + output::SEPARATOR + area + '\n';
}

std::shared_ptr<sf::Shape> TriangleAdapterShape::GetShape() const
{
  return m_triangle.GetShape();
}

bool TriangleAdapterShape::Contains(const sf::Vector2f &point) const
{
  return m_triangle.GetShape()->getGlobalBounds().contains(point);
}

void TriangleAdapterShape::Move(const sf::Vector2f &delta)
{
  m_triangle.GetShape()->move(delta);
}

void TriangleAdapterShape::Accept(IShapeVisitor &visitor)
{
  visitor.Visit(*this);
}

ShapeMemento TriangleAdapterShape::SaveState() const
{
  ShapeMemento state;
  const std::shared_ptr<sf::Shape> s = m_triangle.GetShape();

  state.SetFillColor(s->getFillColor());
  state.SetOutlineColor(s->getOutlineColor());
  state.SetThickness(s->getOutlineThickness());
  state.SetTransform(s->getTransform());

  return state;
}

void TriangleAdapterShape::RestoreState(const ShapeMemento &lastState)
{
  const std::shared_ptr<sf::Shape> s = m_triangle.GetShape();

  s->setFillColor(lastState.GetFillColor());
  s->setOutlineColor(lastState.GetOutlineColor());
  s->setOutlineThickness(lastState.GetThickness());

  sf::Vector2f pos = lastState.GetTransform().transformPoint({0.f, 0.f});
  s->setPosition(pos);
}

double TriangleAdapterShape::GetLineLength(const sf::Vector2f &position1, const sf::Vector2f &position2) const
{
  const double powX = std::pow(position1.x - position2.x, 2);
  const double powY = std::pow(position1.y - position2.y, 2);
  return std::sqrt(powX + powY);
}
