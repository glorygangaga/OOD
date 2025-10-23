#pragma once

#include "include/shapes/SFML/IDrawableShape.hpp"
#include "include/shapes/SFML/SfmlRectangle.hpp"

class RectangleAdapterShape : public IDrawableShape
{
public:
  RectangleAdapterShape(const sf::Vector2f &p1, const sf::Vector2f &p2);

  double GetArea() const override;
  double GetPerimeter() const override;
  std::string ToString() const override;
  std::shared_ptr<sf::Shape> GetShape() const override;

  double GetWidth() const;
  double GetHeight() const;

private:
  SfmlRectangle m_rectangle;
  double m_width, m_height;
};
