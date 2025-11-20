#include "include/tools/states/ChangeColorThickness.hpp"

void ChangeColorThickness::HandleEvent(CCanvas *canvas)
{
  const auto shapes = canvas->GetAllSelectedShapes();

  if (shapes.empty())
    return;

  for (const auto s : shapes)
    canvas->ExecuteCommand(std::make_unique<ChangeColorCommand>(s, m_color));
}