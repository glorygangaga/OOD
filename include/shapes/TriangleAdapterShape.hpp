#pragma once

#include "include/shapes/SFML/IDrawableShape.hpp"
#include "include/shapes/SFML/SfmlTriangle.hpp"

class TriangleAdapterShape : public IDrawableShape
{
public:
  TriangleAdapterShape(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3);

  double GetArea() const override;
  double GetPerimeter() const override;
  std::string ToString() const override;

  std::shared_ptr<sf::Shape> GetShape() const override;
  bool Contains(const sf::Vector2f &point) const override;
  void Move(const sf::Vector2f &delta) override;

  sf::Vector2f GetP1() const;
  sf::Vector2f GetP2() const;
  sf::Vector2f GetP3() const;

private:
  SfmlTriangle m_triangle;
  sf::Vector2f m_p1, m_p2, m_p3;

  double GetLineLength(const sf::Vector2f &position1, const sf::Vector2f &position2) const;
};
