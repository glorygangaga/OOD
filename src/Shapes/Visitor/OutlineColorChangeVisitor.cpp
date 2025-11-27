#include "include/shapes/Visitor/OutlineColorChangeVisitor.hpp"
#include "include/shapes/CircleAdapterShape.hpp"
#include "include/shapes/TriangleAdapterShape.hpp"
#include "include/shapes/RectangleAdapterShape.hpp"

void OutlineColorChangeVisitor::Visit(CircleAdapterShape &circle)
{
  circle.GetShape()->setOutlineColor(m_newColor);
}

void OutlineColorChangeVisitor::Visit(RectangleAdapterShape &rectangle)
{
  rectangle.GetShape()->setOutlineColor(m_newColor);
}

void OutlineColorChangeVisitor::Visit(TriangleAdapterShape &triangle)
{
  triangle.GetShape()->setOutlineColor(m_newColor);
}
