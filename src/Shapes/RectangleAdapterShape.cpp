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

std::vector<ShapeMemento> RectangleAdapterShape::SaveState() const
{
  std::vector<ShapeMemento> states(1);

  const std::shared_ptr<sf::Shape> s = m_rectangle.GetShape();

  states[0].SetFillColor(s->getFillColor());
  states[0].SetOutlineColor(s->getOutlineColor());
  states[0].SetThickness(s->getOutlineThickness());
  states[0].SetPosition(s->getPosition());

  return states;
}

void RectangleAdapterShape::RestoreState(const std::vector<ShapeMemento> &lastState)
{
  const std::shared_ptr<sf::Shape> s = m_rectangle.GetShape();

  s->setFillColor(lastState[0].GetFillColor());
  s->setOutlineColor(lastState[0].GetOutlineColor());
  s->setOutlineThickness(lastState[0].GetThickness());
  s->setPosition(lastState[0].GetPosition());
}

size_t RectangleAdapterShape::GetStateSize() const
{
  return 1;
}

double RectangleAdapterShape::GetWidth() const
{
  return m_width;
}

double RectangleAdapterShape::GetHeight() const
{
  return m_height;
}
