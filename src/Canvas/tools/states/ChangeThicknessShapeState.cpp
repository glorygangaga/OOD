#include "include/tools/states/ChangeThicknessShapeState.hpp"

void ChangeThicknessShapeState::HandleEvent(CCanvas *canvas)
{
  auto shapes = canvas->GetAllSelectedShapes();

  if (shapes.empty())
    return;

  canvas->ExecuteCommand(std::make_unique<ChangeThicknessCommand>(shapes, m_thickness));
}