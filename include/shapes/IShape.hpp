#pragma once

#include <cmath>
#include <memory>
#include "include/Constants.hpp"

class IShape
{
public:
  virtual double GetArea() const = 0;
  virtual double GetPerimeter() const = 0;
  virtual std::string ToString() const = 0;
};