#include "include/tools/states/LoadBinState.hpp"

void LoadBinState::HandleEvent(CCanvas *canvas)
{
  ShapeBuilder builder;
  BinaryShapeLoader loader(builder);

  auto shapes = loader.Load(inputs::BIN_FILENAME);

  if (!shapes.empty())
  {
    auto prevShapes = canvas->GetShapes();
    canvas->ClearCanvas();

    for (auto &s : shapes)
      canvas->PushShape(s);

    canvas->ExecuteCommand(std::make_unique<LoadCommand>(canvas, prevShapes));
  }
}