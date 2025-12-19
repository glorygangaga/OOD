#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "include/tools/save/IShapeBuilder.hpp"
#include "include/shapes/SFML/IDrawableShape.hpp"

class ShapeLoader
{
protected:
  IShapeBuilder &builder;

public:
  ShapeLoader(IShapeBuilder &b) : builder(b) {}

  virtual ~ShapeLoader() = default;

  std::vector<std::shared_ptr<IDrawableShape>> Load(const std::string &filename);

protected:
  virtual void BeginOpen(const std::string &filename) = 0;
  virtual void ReadType() = 0;
  virtual void ReadExtra() = 0;
  virtual void ReadPosition() = 0;
  virtual bool HasMore() = 0;
  virtual void EndOpen() = 0;
};
