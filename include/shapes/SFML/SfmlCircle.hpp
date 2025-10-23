#pragma once

#include "SfmlShape.hpp"

class SfmlCircle : public SfmlShape<sf::CircleShape>
{
public:
  SfmlCircle(const sf::Vector2f &center, const double radius);
};
