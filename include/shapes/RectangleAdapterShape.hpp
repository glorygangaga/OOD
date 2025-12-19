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
  bool Contains(const sf::Vector2f &point) const override;
  void Move(const sf::Vector2f &delta) override;
  void Accept(IShapeVisitor &visitor) override;
  std::vector<ShapeMemento> SaveState() const override;
  void RestoreState(const std::vector<ShapeMemento> &lastState) override;
  size_t GetStateSize() const override;
  void SerializeToBinary(std::ostream &out) const override;
  void SerializeToText(std::ostream &out) const override;

  double GetWidth() const;
  double GetHeight() const;

private:
  SfmlRectangle m_rectangle;
  sf::Vector2f m_p1, m_p2;
  double m_width, m_height;
};
