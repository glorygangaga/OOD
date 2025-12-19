#include "include/tools/commands/ChangeThicknessCommand.hpp"

ChangeThicknessCommand::ChangeThicknessCommand(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const float newThickness)
    : m_shapes(shapes), m_newThickness(newThickness)
{
  for (auto &s : shapes)
    m_before.push_back(s->SaveState());
}

void ChangeThicknessCommand::Execute()
{
  ThicknessChangeVisitor visitor(m_newThickness);
  for (auto &s : m_shapes)
    s->Accept(visitor);
}

void ChangeThicknessCommand::Undo()
{
  if (m_before.empty())
    return;

  for (size_t i = 0; i < m_shapes.size(); i++)
  {
    ThicknessChangeVisitor visitor(m_before[i][0].GetThickness());
    m_shapes[i]->Accept(visitor);
  }
}