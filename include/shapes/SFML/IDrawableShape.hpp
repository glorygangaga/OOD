#pragma once

#include <SFML/Graphics.hpp>
#include "include/shapes/IShape.hpp"
#include "include/shapes/Visitor/IShapeVisitor.hpp"
#include "include/shapes/ShapeMemento.hpp"

class IDrawableShape : public IShape
{
public:
  virtual std::shared_ptr<sf::Shape> GetShape() const = 0;
  virtual bool Contains(const sf::Vector2f &point) const = 0;
  virtual void Move(const sf::Vector2f &delta) = 0;
  virtual void Accept(IShapeVisitor &visitor) = 0;

  virtual std::vector<ShapeMemento> SaveState() const = 0;
  virtual void RestoreState(const std::vector<ShapeMemento> &lastState) = 0;

  virtual size_t GetStateSize() const = 0;
};
