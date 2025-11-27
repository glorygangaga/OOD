#pragma once

#include <vector>
#include <memory>

#include "include/tools/commands/ICommand.hpp"
#include "include/shapes/SFML/IDrawableShape.hpp"
#include "include/CCanvas.hpp"

class UngroupShapesCommand : public ICommand
{
public:
  UngroupShapesCommand(CCanvas *canvas);

  void Execute() override;
  void Undo() override;

private:
  std::vector<std::shared_ptr<IDrawableShape>> m_before;
  CCanvas *m_canvas;
};
