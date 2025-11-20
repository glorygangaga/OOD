#pragma once

#include "include/tools/states/IToolState.hpp"
#include "include/CCanvas.hpp"
#include "include/tools/commands/ChangeThicknessCommand.hpp"

class ChangeThicknessShapeState : public IToolState
{
public:
  ChangeThicknessShapeState(const unsigned int thickness) : m_thickness(thickness) {}

  void HandleEvent(CCanvas *canvas) override;

private:
  unsigned int m_thickness;
};
