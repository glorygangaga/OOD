#include "include/tools/commands/AddShapeCommand.hpp"

void AddShapeCommand::Execute()
{
  m_canvas->PushShape(m_shape);
}