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

  double GetRadius() const;

private:
  SfmlCircle m_circle;
  double m_radius;
};
