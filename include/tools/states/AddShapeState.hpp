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
  AddShapeState(const enum SHAPES_TYPE &shape_type, const sf::Vector2f &startPos) : m_shape_type(shape_type), m_startPos(startPos) {};

  void HandleEvent(CCanvas *canvas) override;

private:
  enum SHAPES_TYPE m_shape_type;
  sf::Vector2f m_startPos;
};
