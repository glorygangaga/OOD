#include "include/shapes/Visitor/ThicknessChangeVisitor.hpp"
#include "include/shapes/CircleAdapterShape.hpp"
#include "include/shapes/TriangleAdapterShape.hpp"
#include "include/shapes/RectangleAdapterShape.hpp"

void ThicknessChangeVisitor::Visit(CircleAdapterShape &circle)
{
  circle.GetShape()->setOutlineThickness(m_newThickness);
}

void ThicknessChangeVisitor::Visit(RectangleAdapterShape &rectangle)
{
  rectangle.GetShape()->setOutlineThickness(m_newThickness);
}

void ThicknessChangeVisitor::Visit(TriangleAdapterShape &triangle)
{
  triangle.GetShape()->setOutlineThickness(m_newThickness);
}
