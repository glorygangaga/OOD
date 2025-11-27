#pragma once

#include "include/shapes/Visitor/IShapeVisitor.hpp"

class ColorChangeVisitor : public IShapeVisitor
{
public:
  ColorChangeVisitor(const sf::Color newColor) : m_newColor(newColor) {}

  void Visit(CircleAdapterShape &circle) override;
  void Visit(RectangleAdapterShape &rectangle) override;
  void Visit(TriangleAdapterShape &triangle) override;

private:
  sf::Color m_newColor;
};
