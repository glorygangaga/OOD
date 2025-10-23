#pragma once

#include <SFML/Graphics.hpp>
#include "include/shapes/IShape.hpp"

class IDrawableShape : public IShape
{
public:
  virtual std::shared_ptr<sf::Shape> GetShape() const = 0;
  virtual bool Contains(const sf::Vector2f &point) const = 0;
  virtual void Move(const sf::Vector2f &delta) = 0;
};
