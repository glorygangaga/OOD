#pragma once

#include "include/shapes/SFML/IDrawableShape.hpp"

class IShapeStrategy
{
public:
  virtual void Save(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const std::string &filename) = 0;
};