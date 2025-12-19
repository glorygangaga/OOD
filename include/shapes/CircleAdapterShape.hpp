#pragma once

#include "include/shapes/SFML/IDrawableShape.hpp"
#include "include/shapes/SFML/SfmlCircle.hpp"

class CircleAdapterShape : public IDrawableShape
{
public:
  CircleAdapterShape(const sf::Vector2f &center, const float radius);

  double GetArea() const override;
  double GetPerimeter() const override;
  std::string ToString() const override;
  std::shared_ptr<sf::Shape> GetShape() const override;
  void Accept(IShapeVisitor &visitor) override;
  std::vector<ShapeMemento> SaveState() const override;
  void RestoreState(const std::vector<ShapeMemento> &lastState) override;
  bool Contains(const sf::Vector2f &point) const override;
  void SerializeToBinary(std::ostream &out) const override;
  void SerializeToText(std::ostream &out) const override;
  void Move(const sf::Vector2f &delta) override;
  size_t GetStateSize() const override;

  float GetRadius() const;

private:
  SfmlCircle m_circle;
  sf::Vector2f m_center;
  float m_radius;
};
