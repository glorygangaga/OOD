#include "include/tools/states/ChangeColorShapeState.hpp"
#include <iostream>

void ChangeColorShapeState::HandleEvent(CCanvas *canvas, const sf::Event &event)
{
  if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
  {
    const auto mousePos = canvas->GetMousePosition();
    const auto shape = canvas->GetShapeByHit(mousePos);

    if (!shape)
      return;

    if (event.key.code == sf::Keyboard::C)
    {
      const sf::Color shapeFillColor = shape->GetShape()->getFillColor();
      const sf::Color newColor = GetNextColor(shapeFillColor);
      canvas->ExecuteCommand(std::make_unique<ChangeColorCommand>(shape, newColor, SHAPE_COLOR_CHANGE::FILL));
    }
    else if (event.key.code == sf::Keyboard::X)
    {
      const sf::Color shapeOutlineColor = shape->GetShape()->getOutlineColor();
      const sf::Color newColor = GetNextColor(shapeOutlineColor);
      canvas->ExecuteCommand(std::make_unique<ChangeColorCommand>(shape, newColor, SHAPE_COLOR_CHANGE::THICKNESS));
    }
  }
}

sf::Color ChangeColorShapeState::GetNextColor(const sf::Color &colorShape) const
{
  int current = static_cast<int>(GetEnumFromColor(colorShape));
  int next = (current + 1) % SHAPE_COLORS_SIZE;

  SHAPE_COLORS nextColorEnum = static_cast<SHAPE_COLORS>(next);
  const auto it = COLORS_MAP.find(nextColorEnum);
  if (it == COLORS_MAP.end())
    return sf::Color::Transparent;

  return it->second;
}

SHAPE_COLORS ChangeColorShapeState::GetEnumFromColor(const sf::Color &color) const
{
  for (const auto &pair : COLORS_MAP)
  {
    if (pair.second == color)
      return pair.first;
  }
  return SHAPE_COLORS::BLACK;
}
