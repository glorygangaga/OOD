#include "include/tools/commands/ChangeThicknessCommand.hpp"

ChangeThicknessCommand::ChangeThicknessCommand(const std::shared_ptr<IDrawableShape> &shape, const float newThickness)
    : m_shape(shape), m_newThickness(newThickness)
{
  m_before = shape->SaveState();
}

void ChangeThicknessCommand::Execute()
{
  ThicknessChangeVisitor visitor(m_newThickness);
  m_shape->Accept(visitor);
}

void ChangeThicknessCommand::Undo()
{
  ThicknessChangeVisitor visitor(m_before.GetThickness());
  m_shape->Accept(visitor);
}