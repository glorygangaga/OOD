#pragma once

#include "include/tools/commands/ICommand.hpp"
#include "include/shapes/SFML/IDrawableShape.hpp"
#include "include/shapes/Visitor/ThicknessChangeVisitor.hpp"

class ChangeThicknessCommand : public ICommand
{
public:
  ChangeThicknessCommand(const std::shared_ptr<IDrawableShape> &shape, const float newThickness);

  void Execute() override;
  void Undo() override;

private:
  std::shared_ptr<IDrawableShape> m_shape;
  float m_newThickness;
  ShapeMemento m_before;
};
