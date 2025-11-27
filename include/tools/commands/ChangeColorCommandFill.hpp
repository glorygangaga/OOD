#pragma once

#include <memory>
#include "include/tools/commands/ICommand.hpp"
#include "include/shapes/SFML/IDrawableShape.hpp"
#include "include/shapes/Visitor/ColorChangeVisitor.hpp"

class ChangeColorCommandFill : public ICommand
{
public:
  ChangeColorCommandFill(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const sf::Color &newColor);
  void Execute() override;
  void Undo() override;

private:
  std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
  sf::Color m_newColor;
  std::vector<ShapeMemento> m_before;
};
