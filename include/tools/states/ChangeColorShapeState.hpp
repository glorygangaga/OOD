#pragma once

#include <memory>
#include "include/tools/states/IToolState.hpp"
#include "include/Constants.hpp"
#include "include/CCanvas.hpp"
#include "include/tools/commands/ChangeColorCommand.hpp"
#include "include/tools/commands/ChangeColorCommandFill.hpp"

class ChangeColorShapeState : public IToolState
{
public:
  ChangeColorShapeState(const sf::Color &color) : m_color(color) {};

  void HandleEvent(CCanvas *canvas) override;

private:
  sf::Color m_color;
};
