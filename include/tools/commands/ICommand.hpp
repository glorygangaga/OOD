#pragma once

#include "include/shapes/ShapeMemento.hpp"

class ICommand
{
public:
  virtual ~ICommand() = default;
  virtual void Execute() = 0;
  virtual void Undo() = 0;
};
