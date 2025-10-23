#pragma once

#include <vector>
#include <memory>

#include "include/shapes/SFML/IDrawableShape.hpp"

class CompositeShape : public IDrawableShape
{
public:
  void Add(const std::shared_ptr<IDrawableShape> &shape);

  void Move(const sf::Vector2f &delta) override;
  bool Contains(const sf::Vector2f &point) const override;
  std::shared_ptr<sf::Shape> GetShape() const override;
  double GetArea() const override;
  double GetPerimeter() const override;
  std::string ToString() const override;

  const std::vector<std::shared_ptr<IDrawableShape>> &GetShapes() const;
  sf::FloatRect GetBounds() const;

private:
  std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
};
