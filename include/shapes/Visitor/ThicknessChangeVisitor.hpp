#pragma once

#include "include/shapes/Visitor/IShapeVisitor.hpp"

class ThicknessChangeVisitor : public IShapeVisitor
{
public:
  ThicknessChangeVisitor(const unsigned int newThickness) : m_newThickness(newThickness) {}

  void Visit(CircleAdapterShape &circle) override;
  void Visit(RectangleAdapterShape &rectangle) override;
  void Visit(TriangleAdapterShape &triangle) override;

private:
  unsigned int m_newThickness;
};
