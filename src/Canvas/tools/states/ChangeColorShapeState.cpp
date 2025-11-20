#include "include/tools/states/ChangeColorShapeState.hpp"
#include <iostream>

void ChangeColorShapeState::HandleEvent(CCanvas *canvas)
{
  const auto shapes = canvas->GetAllSelectedShapes();

  if (shapes.empty())
    return;

  for (const auto s : shapes)
  {
    canvas->ExecuteCommand(std::make_unique<ChangeColorCommandFill>(s, m_color));
  }
}
