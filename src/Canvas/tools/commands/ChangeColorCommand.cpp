#include "include/tools/commands/ChangeColorCommand.hpp"

ChangeColorCommand::ChangeColorCommand(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const sf::Color &newColor)
    : m_shapes(shapes), m_newColor(newColor)
{
  for (auto &s : shapes)
    m_before.push_back(s->SaveState());
}

void ChangeColorCommand::Execute()
{
  OutlineColorChangeVisitor visitor(m_newColor);
  for (auto &s : m_shapes)
    s->Accept(visitor);
}

void ChangeColorCommand::Undo()
{
  if (m_before.empty())
    return;

  for (size_t i = 0; i < m_shapes.size(); i++)
  {
    OutlineColorChangeVisitor visitor(m_before[i][0].GetOutlineColor());
    m_shapes[i]->Accept(visitor);
  }
}