#pragma once

#include <memory>
#include "include/tools/states/IToolState.hpp"
#include "include/tools/commands/AddShapeCommand.hpp"

#include "include/shapes/CircleAdapterShape.hpp"
#include "include/shapes/RectangleAdapterShape.hpp"
#include "include/shapes/TriangleAdapterShape.hpp"

class AddShapeState : public IToolState
{
public:
  void HandleEvent(CCanvas *canvas, const sf::Event &event) override;
};
