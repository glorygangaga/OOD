#pragma once

#include "include/tools/commands/ICommand.hpp"
#include "include/CCanvas.hpp"
#include "include/shapes/SFML/IDrawableShape.hpp"

class DragCommand : public ICommand
{
public:
  DragCommand(const std::vector<std::shared_ptr<IDrawableShape>> &shapes);

  void Execute() override;
  void Undo() override;

private:
  std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
  std::vector<ShapeMemento> m_before;
};
