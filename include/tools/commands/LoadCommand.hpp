#pragma once

#include <memory>
#include "include/shapes/SFML/IDrawableShape.hpp"
#include "include/tools/commands/ICommand.hpp"
#include "include/CCanvas.hpp"

class LoadCommand : public ICommand
{
public:
  LoadCommand(CCanvas *canvas, std::vector<std::shared_ptr<IDrawableShape>> &shapes) : m_canvas(canvas), m_shapes(shapes) {};
  void Execute() override;
  void Undo() override;

private:
  CCanvas *m_canvas;
  std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
};
