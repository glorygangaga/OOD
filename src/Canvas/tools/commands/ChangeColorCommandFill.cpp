#include "include/tools/commands/ChangeColorCommandFill.hpp"

ChangeColorCommandFill::ChangeColorCommandFill(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const sf::Color &newColor)
    : m_shapes(shapes), m_newColor(newColor)
{
  for (auto &s : shapes)
    m_before.push_back(s->SaveState());
}

void ChangeColorCommandFill::Execute()
{
  ColorChangeVisitor visitor(m_newColor);
  for (auto &s : m_shapes)
    s->Accept(visitor);
}

void ChangeColorCommandFill::Undo()
{
  for (size_t i = 0; i < m_shapes.size(); i++)
  {
    ColorChangeVisitor visitor(m_before[i][0].GetFillColor());
    m_shapes[i]->Accept(visitor);
  }
}