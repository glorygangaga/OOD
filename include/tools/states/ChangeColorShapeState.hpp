#pragma once

#include <memory>
#include "include/tools/states/IToolState.hpp"
#include "include/Constants.hpp"
#include "include/CCanvas.hpp"
#include "include/tools/commands/ChangeColorCommand.hpp"

class ChangeColorShapeState : public IToolState
{
public:
  void HandleEvent(CCanvas *canvas, const sf::Event &event) override;

private:
  sf::Color GetNextColor(const sf::Color &colorShape) const;
  SHAPE_COLORS GetEnumFromColor(const sf::Color &color) const;
};
