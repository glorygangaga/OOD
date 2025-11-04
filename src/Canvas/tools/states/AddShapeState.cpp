#include "include/tools/states/AddShapeState.hpp"

void AddShapeState::HandleEvent(CCanvas *canvas, const sf::Event &event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    const sf::Vector2f mousePos = canvas->GetMousePosition();
    std::shared_ptr<IDrawableShape> newShape;

    if (event.key.code == sf::Keyboard::Num1)
      newShape = std::make_shared<CircleAdapterShape>(mousePos, 50);
    else if (event.key.code == sf::Keyboard::Num2)
    {
      const sf::Vector2f p2(mousePos.x, mousePos.y + 100);
      const sf::Vector2f p3(mousePos.x + 100, mousePos.y + 50);
      newShape = std::make_shared<TriangleAdapterShape>(mousePos, p2, p3);
    }
    else if (event.key.code == sf::Keyboard::Num3)
    {
      const sf::Vector2f p2(mousePos.x + 100, mousePos.y + 100);
      newShape = std::make_shared<RectangleAdapterShape>(mousePos, p2);
    }
    else
      return;

    canvas->ExecuteCommand(std::make_unique<AddShapeCommand>(canvas, newShape));
  }
}