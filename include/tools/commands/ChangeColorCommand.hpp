#pragma once

#include <memory>
#include "include/tools/commands/ICommand.hpp"
#include "include/shapes/SFML/IDrawableShape.hpp"

class ChangeColorCommand : public ICommand
{
public:
  ChangeColorCommand(const std::shared_ptr<IDrawableShape> &shape, const sf::Color &newColor, enum SHAPE_COLOR_CHANGE shapeType)
      : m_shape(shape), m_newColor(newColor), m_shapeType(shapeType) {}

  void Execute() override;

private:
  std::shared_ptr<IDrawableShape> m_shape;
  sf::Color m_newColor;
  SHAPE_COLOR_CHANGE m_shapeType;
};
