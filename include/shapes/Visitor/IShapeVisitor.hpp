#pragma once

#include <SFML/Graphics.hpp>

class CircleAdapterShape;
class RectangleAdapterShape;
class TriangleAdapterShape;

class IShapeVisitor
{
public:
  virtual void Visit(CircleAdapterShape &circle) = 0;
  virtual void Visit(RectangleAdapterShape &rectangle) = 0;
  virtual void Visit(TriangleAdapterShape &triangle) = 0;
};
