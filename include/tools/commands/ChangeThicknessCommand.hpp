#pragma once

#include "include/tools/commands/ICommand.hpp"
#include "include/shapes/SFML/IDrawableShape.hpp"

class ChangeThicknessCommand : public ICommand
{
public:
  ChangeThicknessCommand(const std::shared_ptr<IDrawableShape> &shape, const float newThickness)
      : m_shape(shape), m_newThickness(newThickness) {}

  void Execute() override;

private:
  std::shared_ptr<IDrawableShape> m_shape;
  float m_newThickness;
};
