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

std::vector<std::shared_ptr<IDrawableShape>> CompositeShape::GetAllShapes()
{
  std::vector<std::shared_ptr<IDrawableShape>> result;

  for (auto s : m_shapes)
    CollectShapes(s, result);

  return result;
}

void CompositeShape::CollectShapes(const std::shared_ptr<IDrawableShape> &shape, std::vector<std::shared_ptr<IDrawableShape>> &outShapes)
{
  auto group = std::dynamic_pointer_cast<CompositeShape>(shape);
  if (group)
    for (const auto &s : group->GetShapes())
      CollectShapes(s, outShapes);
  else
    outShapes.push_back(shape);
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

std::vector<ShapeMemento> CompositeShape::SaveState() const
{
  std::vector<ShapeMemento> result;
  result.reserve(GetStateSize());

  ShapeMemento own;
  result.push_back(own);

  for (auto &child : m_shapes)
  {
    auto cs = child->SaveState();
    result.insert(result.end(), cs.begin(), cs.end());
  }

  return result;
}

void CompositeShape::RestoreState(const std::vector<ShapeMemento> &lastState)
{
  size_t idx = 1;

  for (auto &child : m_shapes)
  {
    const size_t sz = child->GetStateSize();

    std::vector<ShapeMemento> sub(
        lastState.begin() + idx,
        lastState.begin() + idx + sz);

    child->RestoreState(sub);

    idx += sz;
  }
}

size_t CompositeShape::GetStateSize() const
{
  size_t sum = 1;
  for (auto &s : m_shapes)
    sum += s->GetStateSize();

  return sum;
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
