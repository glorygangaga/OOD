#pragma once

#include <include/Constants.hpp>
#include <cmath>
#include <memory>

class IShape
{
public:
  virtual double GetArea() const = 0;
  virtual double GetPerimeter() const = 0;
  virtual std::string ToString() const = 0;
};
