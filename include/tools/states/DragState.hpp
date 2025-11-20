#pragma once

#include "include/tools/states/IToolState.hpp"
#include "include/tools/commands/DragCommand.hpp"

class DragState : public IToolState
{
public:
  void HandleEvent(CCanvas *canvas) override;
};
