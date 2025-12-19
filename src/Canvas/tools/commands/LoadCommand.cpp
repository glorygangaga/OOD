#include "include/tools/commands/LoadCommand.hpp"

void LoadCommand::Execute()
{
}

void LoadCommand::Undo()
{
  m_canvas->ClearCanvas();

  for (auto &s : m_shapes)
    m_canvas->PushShape(s);
}
