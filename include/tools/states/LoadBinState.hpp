#pragma once

#include "include/CCanvas.hpp"
#include "include/tools/states/IToolState.hpp"
#include "include/tools/save/ShapeBuilder.hpp"
#include "include/tools/save/BinaryShapeLoader.hpp"
#include "include/tools/commands/LoadCommand.hpp"

class LoadBinState : public IToolState
{
public:
  void HandleEvent(CCanvas *canvas) override;
};
