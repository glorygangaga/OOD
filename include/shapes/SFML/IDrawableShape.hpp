#pragma once

#include <SFML/Graphics.hpp>
#include "include/shapes/IShape.hpp"

class IDrawableShape : public IShape
{
public:
  virtual std::shared_ptr<sf::Shape> GetShape() const = 0;
};
