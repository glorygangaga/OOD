#pragma once

#include "include/tools/states/IToolState.hpp"
#include "include/CCanvas.hpp"
#include "include/tools/commands/ChangeThicknessCommand.hpp"

class ChangeThicknessShapeState : public IToolState
{
public:
  void HandleEvent(CCanvas *canvas, const sf::Event &event) override;
};
