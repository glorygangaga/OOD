#include "include/tools/commands/ChangeColorCommand.hpp"

void ChangeColorCommand::Execute()
{
  m_shape->GetShape()->setOutlineColor(m_newColor);
}