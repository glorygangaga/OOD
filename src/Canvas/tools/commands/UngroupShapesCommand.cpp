#include "include/tools/commands/UngroupShapesCommand.hpp"

UngroupShapesCommand::UngroupShapesCommand(CCanvas *canvas) : m_canvas(canvas) {}

void UngroupShapesCommand::Execute()
{
  m_before = m_canvas->GetSelected();
  m_canvas->UngroupShapes(m_before);
}

void UngroupShapesCommand::Undo()
{
  m_canvas->GroupShapes(m_before);
}
