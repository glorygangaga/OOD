#pragma once

#include "include/tools/states/IToolState.hpp"
#include "include/tools/commands/ChangeColorCommand.hpp"
#include "include/CCanvas.hpp"

class ChangeColorThickness : public IToolState
{
public:
  ChangeColorThickness(const sf::Color &color) : m_color(color) {}
  void HandleEvent(CCanvas *canvas) override;

private:
  sf::Color m_color;
};
