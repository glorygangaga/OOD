#include "include/tools/states/ChangeColorShapeState.hpp"
#include <iostream>

void ChangeColorShapeState::HandleEvent(CCanvas *canvas)
{
  const auto shapes = canvas->GetAllSelectedShapes();

  if (shapes.empty())
    return;

  canvas->ExecuteCommand(std::make_unique<ChangeColorCommandFill>(shapes, m_color));
}
