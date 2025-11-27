#include "include/tools/states/ChangeColorThickness.hpp"

void ChangeColorThickness::HandleEvent(CCanvas *canvas)
{
  const auto shapes = canvas->GetAllSelectedShapes();

  if (shapes.empty())
    return;

  canvas->ExecuteCommand(std::make_unique<ChangeColorCommand>(shapes, m_color));
}