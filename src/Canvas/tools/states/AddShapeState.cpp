#include "include/tools/states/AddShapeState.hpp"

void AddShapeState::HandleEvent(CCanvas *canvas)
{
  std::shared_ptr<IDrawableShape> newShape;

  switch (m_shape_type)
  {
  case SHAPES_TYPE::CIRCLE_T:
    newShape = std::make_shared<CircleAdapterShape>(sf::Vector2f(0, m_startPos.y), 50);
    break;
  case SHAPES_TYPE::RECTANGLE_T:
    newShape = std::make_shared<RectangleAdapterShape>(sf::Vector2f(0, m_startPos.y), sf::Vector2f(100, m_startPos.y + 100));
    break;
  case SHAPES_TYPE::TRIANGLE_T:
    newShape = std::make_shared<TriangleAdapterShape>(sf::Vector2f(0, m_startPos.y), sf::Vector2f(0, m_startPos.y + 100), sf::Vector2f(100, m_startPos.y + 50));
    break;
  default:
    return;
  }

  canvas->ExecuteCommand(std::make_unique<AddShapeCommand>(canvas, newShape));
}