#include "include/tools/states/LoadTxtState.hpp"

void LoadTxtState::HandleEvent(CCanvas *canvas)
{
  ShapeBuilder builder;
  TxtShapeLoader loader(builder);

  auto shapes = loader.Load(inputs::TEXT_FILENAME);

  if (!shapes.empty())
  {
    auto prevShapes = canvas->GetShapes();
    canvas->ClearCanvas();

    for (auto &s : shapes)
      canvas->PushShape(s);

    canvas->ExecuteCommand(std::make_unique<LoadCommand>(canvas, prevShapes));
  }
}