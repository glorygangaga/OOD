#include "include/tools/commands/ChangeThicknessCommand.hpp"

void ChangeThicknessCommand::Execute()
{
  m_shape->GetShape()->setOutlineThickness(m_newThickness);
}