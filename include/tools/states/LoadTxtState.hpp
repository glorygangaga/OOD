#pragma once

#include "include/tools/states/IToolState.hpp"
#include "include/CCanvas.hpp"
#include "include/tools/save/ShapeBuilder.hpp"
#include "include/tools/save/TxtShapeLoader.hpp"
#include "include/tools/commands/LoadCommand.hpp"

class LoadTxtState : public IToolState
{
public:
  void HandleEvent(CCanvas *canvas) override;
};
