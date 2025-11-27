#pragma once

#include "include/shapes/SFML/IDrawableShape.hpp"
#include "include/shapes/SFML/SfmlCircle.hpp"

class CircleAdapterShape : public IDrawableShape
{
public:
  CircleAdapterShape(const sf::Vector2f &center, const double radius);

  double GetArea() const override;
  double GetPerimeter() const override;
  std::string ToString() const override;
  std::shared_ptr<sf::Shape> GetShape() const override;
  void Accept(IShapeVisitor &visitor) override;
  ShapeMemento SaveState() const override;
  void RestoreState(const ShapeMemento &lastState) override;
  bool Contains(const sf::Vector2f &point) const override;
  void Move(const sf::Vector2f &delta) override;

  double GetRadius() const;

private:
  SfmlCircle m_circle;
  double m_radius;
};
