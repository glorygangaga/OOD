#pragma once

#include <fstream>
#include "include/tools/save/IShapeStrategy.hpp"

class TxtShapeStrategy : public IShapeStrategy
{
public:
  void Save(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const std::string &filename) override;
};
