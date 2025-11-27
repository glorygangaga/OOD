#include "include/shapes/Visitor/ColorChangeVisitor.hpp"
#include "include/shapes/CircleAdapterShape.hpp"
#include "include/shapes/TriangleAdapterShape.hpp"
#include "include/shapes/RectangleAdapterShape.hpp"

void ColorChangeVisitor::Visit(CircleAdapterShape &circle)
{
  circle.GetShape()->setFillColor(m_newColor);
}

void ColorChangeVisitor::Visit(RectangleAdapterShape &rectangle)
{
  rectangle.GetShape()->setFillColor(m_newColor);
}

void ColorChangeVisitor::Visit(TriangleAdapterShape &triangle)
{
  triangle.GetShape()->setFillColor(m_newColor);
}
