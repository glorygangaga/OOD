#include "include/shapes/CompositeShape.hpp"

void CompositeShape::Add(const std::shared_ptr<IDrawableShape> &shape)
{
  m_shapes.push_back(shape);
}

void CompositeShape::Move(const sf::Vector2f &delta)
{
  for (auto &s : m_shapes)
    s->Move(delta);
}

bool CompositeShape::Contains(const sf::Vector2f &point) const
{
  for (auto &s : m_shapes)
    if (s->Contains(point))
      return true;
  return false;
}

std::shared_ptr<sf::Shape> CompositeShape::GetShape() const
{
  sf::FloatRect bounds = GetBounds();
  auto rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(bounds.width, bounds.height));
  rect->setPosition(bounds.left, bounds.top);
  rect->setFillColor(sf::Color::Transparent);
  rect->setOutlineThickness(0);
  return rect;
}

const std::vector<std::shared_ptr<IDrawableShape>> &CompositeShape::GetShapes() const
{
  return m_shapes;
}

double CompositeShape::GetArea() const
{
  double sum = 0;
  for (auto &s : m_shapes)
    sum += s->GetArea();
  return sum;
}

double CompositeShape::GetPerimeter() const
{
  double sum = 0;
  for (auto &s : m_shapes)
    sum += s->GetPerimeter();
  return sum;
}

std::string CompositeShape::ToString() const
{
  std::string out = "Group: [\\n";
  for (auto &s : m_shapes)
    out += s->ToString() + "\\n";
  return out + "]";
}

void CompositeShape::Accept(IShapeVisitor &visitor)
{
  return;
}

ShapeMemento CompositeShape::SaveState() const
{
  return ShapeMemento();
}

void CompositeShape::RestoreState(const ShapeMemento &lastState)
{
  return;
}

sf::FloatRect CompositeShape::GetBounds() const
{
  if (m_shapes.empty())
    return sf::FloatRect();

  sf::FloatRect bounds = m_shapes.front()->GetShape()->getGlobalBounds();

  for (auto &c : m_shapes)
  {
    sf::FloatRect child = c->GetShape()->getGlobalBounds();
    float left = std::min(bounds.left, child.left);
    float top = std::min(bounds.top, child.top);
    float right = std::max(bounds.left + bounds.width, child.left + child.width);
    float bottom = std::max(bounds.top + bounds.height, child.top + child.height);

    bounds = {left, top, right - left, bottom - top};
  }

  return bounds;
}
