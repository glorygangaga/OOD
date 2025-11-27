#include "include/tools/commands/GroupShapesCommand.hpp"

GroupShapesCommand::GroupShapesCommand(CCanvas *canvas) : m_canvas(canvas) {}

void GroupShapesCommand::Execute()
{
  auto newShape = m_canvas->GroupShapes(m_canvas->GetSelected());
  m_before.push_back(newShape);
}

void GroupShapesCommand::Undo()
{
  m_canvas->UngroupShapes(m_before);
}
