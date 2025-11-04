#include "include/tools/states/ChangeThicknessShapeState.hpp"

void ChangeThicknessShapeState::HandleEvent(CCanvas *canvas, const sf::Event &event)
{
  if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
  {
    const auto mousePos = canvas->GetMousePosition();
    const auto shape = canvas->GetShapeByHit(mousePos);

    if (!shape)
      return;

    const float thikness = shape->GetShape()->getOutlineThickness();

    if (event.key.code == sf::Keyboard::Up)
    {
      canvas->ExecuteCommand(std::make_unique<ChangeThicknessCommand>(shape, thikness + 1));
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
      if (thikness - 1 > 0)
        canvas->ExecuteCommand(std::make_unique<ChangeThicknessCommand>(shape, thikness - 1));
    }
  }
}