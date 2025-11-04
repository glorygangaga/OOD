#pragma once

#include <memory>
#include "include/tools/commands/ICommand.hpp"
#include "include/CCanvas.hpp"

class AddShapeCommand : public ICommand
{
public:
  AddShapeCommand(CCanvas *canvas, std::shared_ptr<IDrawableShape> shape)
      : m_canvas(canvas), m_shape(shape) {}

  void Execute() override;

private:
  CCanvas *m_canvas;
  std::shared_ptr<IDrawableShape> m_shape;
};
